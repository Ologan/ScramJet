#include "sjfunctions.h"
#include "sjalloc.h"

#include <sys/param.h>
#include <stdio.h>

typedef void (*sj_buffer_process_fn)(void*, sj_pos_t, size_t, void*);

static inline void
_sj_process_vector_buffered( const sj_vector *vector, sj_buffer_process_fn process_buffer_fn, void* args )
{
    const size_t BUFFER_SIZE = 4096;
    char* buffer = sj_malloc( BUFFER_SIZE );

    // Split data into n chunks. Each chunk will be loaded in the buffer
    // separately
    int num_chunks = (vector->size*vector->elemsize + BUFFER_SIZE + 1) / BUFFER_SIZE;    // Round up division

    // Number of elements per (full) buffer
    int elems_per_buffer = BUFFER_SIZE/vector->elemsize;

    for ( int c = 0; c < num_chunks; c++ )
    {
        // How many elements in the buffer. Will be equal to BUFFER_SIZE/sizeof(element) for all j < n-1.
        // (that is, all the buffers will be full up until the last buffer)
        size_t elems_in_buffer = (c == num_chunks-1) ? (vector->size - c*elems_per_buffer) : elems_per_buffer;

        size_t buffer_bytes = elems_in_buffer*vector->elemsize;
        sj_pos_t start_pos = c*elems_per_buffer;

        printf("%zi %zi\n", start_pos, elems_in_buffer);

        // 1. LOAD INTO BUFFER
        memcpy( buffer, &vector->data.c[c*BUFFER_SIZE], buffer_bytes );

        // 2. PROCESS BUFFER
        process_buffer_fn( (void*) buffer, start_pos, elems_in_buffer, args );

        // 3. STORE BUFFER BACK
        memcpy( &vector->data.c[c*BUFFER_SIZE], buffer, buffer_bytes );
    }

    sj_free( buffer );
}

/*************************************************************************/
static inline sj_type
_sj_best_datatype( sj_type t1, sj_type t2 )
{
    return MAX( t1, t2 );
}

/*************************************************************************/
struct _sj_vector_sum_arg_t
{
    const sj_vector* b;
    sj_vector *dest;
};

void _sj_vector_sum_buffer( void *vbuffer, sj_pos_t start_pos, size_t num_elements, void *vargs )
{
    struct _sj_vector_sum_arg_t *args = (struct _sj_vector_sum_arg_t*) vargs;
    int32_t *buffer = (int32_t*) vbuffer;

    for ( size_t i = 0; i < num_elements; i++ )
    {
        args->dest->data.i32[start_pos+i] = buffer[i] + args->b->data.i32[start_pos+i];
    }
}

sj_vector*
sj_vector_sum( const sj_vector* a, const sj_vector* b, sj_vector* dest )
{
    size_t dest_size = MIN( a->size, b->size );
    sj_type best_datatype = _sj_best_datatype( a->type, b->type );
    if ( dest == NULL )
    {
        dest = sj_vector_create( best_datatype, dest_size );
    }

    //TODO: What to do when datatype(a) != datatype(b)?
    sj_vector_cast( dest, best_datatype );

    struct _sj_vector_sum_arg_t args;
    args.b = b;
    args.dest = dest;

    _sj_process_vector_buffered( a, _sj_vector_sum_buffer, &args );

    return dest;
}
