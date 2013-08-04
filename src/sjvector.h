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
#pragma once
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define CACHE_ALIGNMENT 64
#define SJ_TYPE_SWITCH switch     // TODO: Make a "switch" statement for each data type

typedef enum
{
    SJ_I32
} sj_type;

typedef enum
{
    SJ_OK,
    SJ_MEMORY_ERROR
} sj_error;

typedef union
{
    int32_t i32;
} sj_value;

typedef struct
{
    size_t   size;
    sj_type  type;
    size_t   elemsize;

    union
    {
        void    *v;
        char    *c;
        int32_t *i32;
    }        data;

    size_t   _alloced_elements;     /* Number of elements alloced */
} sj_vector;

typedef size_t sj_pos_t;

#define SJ_ITERATE_VECTOR(v, p)  for ( char *p = (v)->data.c; p < (v)->data.c+((v)->size*(v)->elemsize); p += (v)->elemsize )

/* Basic vector operations */
sj_vector* sj_vector_create( sj_type type, size_t initial_size );
sj_vector* sj_vector_clone( const sj_vector* vector );
sj_error sj_append_element( sj_vector* vector, sj_value value );
void sj_vector_set( sj_vector* vector, sj_value value );
void sj_vector_cast( sj_vector* vector, sj_type to_type );
void sj_vector_free( sj_vector* vector );
void sj_vector_print( const sj_vector* vector );
sj_value sj_get_value( const sj_vector* vector, sj_pos_t pos);
void* sj_get_value_ptr( const sj_vector* vector, sj_pos_t pos);
size_t sj_typesize( sj_type type );
