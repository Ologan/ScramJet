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
#include <string.h>
#include <stdint.h>

#define CACHE_ALIGNMENT 64

void* sj_malloc( size_t size );

typedef enum
{
    SJ_I32
} sj_type;

typedef union
{
    int32_t i32;
} sj_value;

typedef union
{
    void    *v;
    char    *c;
    int32_t *i32;
} sj_data;

typedef struct
{
    int      ndims;
    size_t  *size;
    sj_type  type;
    size_t   typesize;
    sj_data *data;
} sj_array;

sj_array* sj_create_array1( sj_type type, size_t size0 );
void sj_sum_constant( sj_array *array, sj_value value );
void sj_free_array( sj_array* array );
void sj_print_array( const sj_array *array );
