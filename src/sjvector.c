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

typedef void (*sj_buffer_process_fn)(void*, size_t, void*);

/*************************************************************************/
sj_vector*
sj_create_vector( sj_type type, size_t initial_size )
{
    sj_vector *vector = malloc( sizeof(sj_vector) );
    vector->type = type;

    switch ( type )
    {
    case SJ_I32:
        vector->elemsize = sizeof(int32_t);
        break;
    }

    vector->size = initial_size;
    vector->data.v = sj_malloc( vector->elemsize*vector->size );
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
sj_append_element( sj_vector *vector, sj_value value )
{
    // Increase vector size in a 10% if necessary
    if ( vector->_alloced_elements == vector->size )
    {
        vector->_alloced_elements += (vector->_alloced_elements / 10) + 1;
        vector->data.v = sj_realloc( vector->data.v, vector->_alloced_elements*vector->elemsize );
        if ( !vector->data.v )
            return SJ_MEMORY_ERROR;
    }

    vector->size++;

    SJ_TYPE_SWITCH
    vector->data.i32[vector->size-1] = value.i32;

    return SJ_OK;
}

/*************************************************************************/
void sj_print_vector( const sj_vector *vector )
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
sj_free_vector( sj_vector *vector )
{
    sj_free( vector->data.v );
    sj_free( vector );
}
