// ScramJet: fast data processing
//
// Copyright 2013 Alejo Sanchez
//
// This file is part of ScramJet
//
// ScramJet is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// ScramJet is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with ScramJet.  If not, see <http://www.gnu.org/licenses/>.
//
#include <stdlib.h>
#include <stdio.h>

#include "sjvector.h"
#include "sjalloc.h"

#define BUFFER_SIZE 4096

/*************************************************************************/
sj_vector*
sj_vector_create( sj_type type, size_t initial_size )
{
    sj_vector *vector = malloc( sizeof(sj_vector) );
    vector->type = type;

    vector->elemsize = sj_typesize( type );
    vector->size = initial_size;
    vector->data.v = sj_calloc( vector->size, vector->elemsize );
    vector->_alloced_elements = vector->size;

    return vector;
}

/*************************************************************************/
/*void
sj_process_array_buffered( sj_array *array, sj_buffer_process_fn process_buffer_fn, void *args )
{
    #pragma omp parallel for
    for ( int i = 0; i < array->ndims; i++ )
    {
        char buffer[BUFFER_SIZE];

        // Split data into n chunks. Each chunk will be loaded in the buffer
        // separately
        size_t numChunks = (array->size[i]*array->elemsize + BUFFER_SIZE - 1) / BUFFER_SIZE;        // Round up division

        // Number of elements per (full) buffer
        size_t elemsPerBuffer = BUFFER_SIZE/array->elemsize;
        for ( size_t j = 0; j < numChunks; j++ )
        {
            // How many elements in the buffer. Will be equal to BUFFER_SIZE/sizeof(element) for all j < n-1.
            // (that is, all the buffers will be full up until the last buffer)
            size_t elementsInBuffer = (j == numChunks-1) ? (array->size[i] - j*elemsPerBuffer) : elemsPerBuffer;

            // 1. LOAD INTO BUFFER
            memcpy( buffer, &array->data->c[j*BUFFER_SIZE], elementsInBuffer*array->elemsize );

            // 2. PROCESS BUFFER
            process_buffer_fn( (void*)buffer, elementsInBuffer, args );

            // 3. STORE BUFFER BACK
            memcpy( &array->data->c[j*BUFFER_SIZE], buffer, elementsInBuffer*array->elemsize );
        }
    }
}*/

/*************************************************************************/
/*void
sj_sum_constant_buffered( void *buffer, size_t elemsInBuffer, void *pValue )
{
    SJ_TYPE_SWITCH
    int32_t *cbuffer = (int32_t*) buffer;           // Casted buffer
    sj_value *value = (sj_value*) pValue;
    for ( size_t i = 0; i < elemsInBuffer; i++ )
        cbuffer[i] += value->i32;
}*/

/*************************************************************************/
/*void
sj_sum_constant( sj_array *array, sj_value value )
{
    sj_process_array_buffered( array, sj_sum_constant_buffered,  &value );
}*/

/*************************************************************************/
sj_error
sj_alloc_more_elements( sj_vector *vector, size_t num_elements )
{
    vector->data.v = sj_realloc( vector->data.v, vector->elemsize*(vector->_alloced_elements+num_elements) );
    if ( !vector->data.v )
        return SJ_MEMORY_ERROR;
    vector->_alloced_elements += num_elements;
}

/*************************************************************************/
sj_error
sj_append_element( sj_vector *vector, sj_value value )
{
    // Increase vector size in a 10% if necessary
    if ( vector->_alloced_elements == vector->size )
    {
        sj_error err = sj_alloc_more_elements( vector, (vector->_alloced_elements/10)+1 );
        if ( err )
            return err;
    }

    vector->size++;

    SJ_TYPE_SWITCH(vector->type)
    {
    case SJ_I32:
        vector->data.i32[vector->size-1] = value.i32;
        break;
    }

    return SJ_OK;
}

/*************************************************************************/
void*
sj_get_value_ptr(const sj_vector* vector, sj_pos_t pos )
{
    return vector->data.c + (vector->elemsize*pos);
}

/*************************************************************************/
sj_value
sj_get_value( const sj_vector* vector, sj_pos_t pos )
{
    void *value_ptr = sj_get_value_ptr( vector, pos );
}

/*************************************************************************/
sj_vector*
sj_vector_clone( const sj_vector* vector )
{
    sj_vector* cloned = sj_vector_create( vector->type, vector->size );
    size_t num_bytes = vector->size*vector->elemsize;
    memcpy( cloned->data.v, vector->data.v, num_bytes );
    return cloned;
}

/*************************************************************************/
void
sj_vector_set( sj_vector* vector, sj_value value )
{
    SJ_TYPE_SWITCH(vector->type)
    {
    case SJ_I32:
        #pragma omp parallel for
        for (size_t i = 0; i < vector->size; i++)
        {
            vector->data.i32[i] = value.i32;
        }
        break;
    }
}

/*************************************************************************/
void
sj_vector_print( const sj_vector* vector )
{
    printf("[");
    for ( size_t i = 0; i < vector->size; i++ )
    {
        printf("%i ", vector->data.i32[i] );
    }
    puts("]");
}

/*************************************************************************/
void
sj_vector_cast( sj_vector* vector, sj_type type )
{
    if ( type == vector->type )
        return;

    size_t new_typesize = sj_typesize( type );
    char *casted_data = sj_calloc( vector->size, new_typesize );

    char *ps = vector->data.c;
    char *pd = casted_data;
    sj_pos_t i;
#define CAST_VALUE(psrc, pdest, typesrc, typedest) *((typedest*) pdest) = (typedest) *((typesrc*) psrc)
    for (sj_pos_t i = 0; i < vector->size; i++)
    {
        // TODO: check ALL possible combinations
        CAST_VALUE( ps, pd, int32_t, int32_t );

        ps += vector->elemsize;
        pd += new_typesize;
    }

    sj_free( vector->data.v );
    vector->data.c = casted_data;
    vector->type = type;
    vector->elemsize = new_typesize;
}

/*************************************************************************/
size_t
sj_typesize( sj_type type )
{
    SJ_TYPE_SWITCH( type ) {
    case SJ_I32: return sizeof(int32_t);
    }
    return 0;
}

/*************************************************************************/
void
sj_vector_free( sj_vector *vector )
{
    sj_free( vector->data.v );
    sj_free( vector );
}
