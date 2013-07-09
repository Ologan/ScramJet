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
#include "sjarray.h"

#define BUFFER_SIZE 4096

void* sj_malloc( size_t size )
{
    void *ptr;
    posix_memalign( &ptr, CACHE_ALIGNMENT, size );
    memset( ptr, 0, size );
    return ptr;
}

sj_array*
sj_create_array1( sj_type type, size_t size0 )
{
    sj_array *array = malloc( sizeof(sj_array) );
    array->ndims = 1;
    array->type = type;

    switch ( type )
    {
    case SJ_I32:
        array->typesize = sizeof(int32_t);
        break;
    }

    array->size = malloc( 1*sizeof(int) );
    array->size[0] = size0;

    array->data = malloc( 1*sizeof(sj_data) );
    array->data[0].v = sj_malloc( array->typesize*size0 );

    return array;
}

void
sj_sum_constant( sj_array *array, sj_value value )
{
    #pragma omp parallel for
    for ( int i = 0; i < array->ndims; i++ )
    {
        char buffer[BUFFER_SIZE];

        // Split data into n chunks. Each chunk will be loaded in the buffer
        // separately
        size_t n = (array->size[i]*sizeof(int32_t) + BUFFER_SIZE - 1) / BUFFER_SIZE;        // Round up division
        for ( size_t j = 0; j < n; j++ )
        {
            // How many elements in the buffer. Will be equal to BUFFER_SIZE/sizeof(element) for all j < n-1.
            // (that is, all the buffers will be full up until the last buffer)
            size_t elementsInBuffer = (j == n-1) ? (array->size[i] - (j*BUFFER_SIZE)/sizeof(int32_t)) : BUFFER_SIZE/sizeof(int32_t);

            // 1. LOAD INTO BUFFER
            memcpy( buffer, array->data->c+(j*BUFFER_SIZE), elementsInBuffer*sizeof(int32_t) );

            // 2. PROCESS BUFFER
            int32_t *cbuffer = (int32_t*) buffer;            // Casted buffer
            for ( size_t k = 0; k < elementsInBuffer; k++ )
            {
                cbuffer[k] += value.i32;
            }

            // 3. STORE BUFFER BACK
            memcpy( array->data->c+(j*BUFFER_SIZE), buffer, elementsInBuffer*sizeof(int32_t) );
        }
    }
}

void
sj_free_array( sj_array *array )
{
    free( array->size );
    free( array->data );
    free( array );
}
