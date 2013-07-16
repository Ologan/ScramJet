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

void *sj_malloc( size_t size );
void *sj_realloc( void *ptr, size_t size );
void *sj_calloc( size_t num, size_t size );
void *sj_crealloc( void *ptr, size_t num, size_t size );
void sj_free( void *ptr );
