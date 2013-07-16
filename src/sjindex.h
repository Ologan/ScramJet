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
#include "sjvector.h"

typedef struct
{

} sj_index;

typedef struct
{

} sj_index_query_result;

typedef enum
{
    SJ_OP_EQ,
    SJ_OP_GT,
    SJ_OP_GE,
    SJ_OP_LT,
    SJ_OP_LE
} sj_operation;

sj_index *sj_build_index( const sj_vector *vector );
sj_index_query_result sj_query_index( sj_index *index, sj_value value, sj_operation op );
void sj_free_index( sj_index *index );
