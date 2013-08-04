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

#include <stdio.h>
#include "sjvector.h"
#include "sjfunctions.h"

int
main( int argc, char *argv[] )
{
    static const int N = 10000;
    sj_vector *vector1 = sj_vector_create( SJ_I32, N );
    sj_vector *vector2 = sj_vector_create( SJ_I32, N );

    sj_value value;
    value.i32 = 1;
    sj_vector_set( vector1, value );

    value.i32 = 2;
    sj_vector_set( vector2, value );

    sj_vector *res = sj_vector_sum( vector1, vector2, NULL );

    sj_vector_print( res );

    sj_vector_free( res );
    sj_vector_free( vector1 );
    sj_vector_free( vector2 );

    return 0;
}
