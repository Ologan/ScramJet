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

int
main( int argc, char *argv[] )
{
    static const int N = 10000;
    sj_vector *vector = sj_create_vector( SJ_I32, N );

    for ( int i = 0; i < N; i++ )
    {
        vector->data.i32[i] = i;
    }
    sj_print_vector( vector );


    sj_free_vector( vector );
    return 0;
}
