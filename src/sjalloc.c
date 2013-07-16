#include "sjalloc.h"
#include <string.h>

/*************************************************************************/
void*
sj_malloc( size_t size )
{
    void *ptr;
    //posix_memalign( &ptr, CACHE_ALIGNMENT, size );  // This throws a compiler warning. Why?
    ptr = malloc( size );
    memset( ptr, 0, size );
    return ptr;
}

/*************************************************************************/
void*
sj_realloc( void *ptr, size_t size )
{
    return realloc( ptr, size );
}

/*************************************************************************/
void
sj_free( void *ptr )
{
    free( ptr );
}
