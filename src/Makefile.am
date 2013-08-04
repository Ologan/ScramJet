AM_CFLAGS           = -I$(top_srcdir)/../../../include -std=c99 -fopenmp -Werror

lib_LTLIBRARIES     = libscramjet.la
bin_PROGRAMS        = main

main_SOURCES        = main.c
main_LDADD          = libscramjet.la

libscramjet_la_SOURCES = sjalloc.c sjalloc.h sjindex.c sjindex.h sjvector.c sjvector.h sjfunctions.c sjfunctions.h
# Version of shared library API
libscramjet_la_LDFLAGS = -version-info 0:0:0

check_PROGRAMS = scramjet_test
TESTS          = scramjet_test

# Test program
#libscramjet_test_SOURCES  = test.c
#libscramjet_test_LDADD    = libscramjet.la
