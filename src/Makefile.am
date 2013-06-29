AM_CFLAGS           = -I$(top_srcdir)/../../../include

lib_LTLIBRARIES     = libscramjet.la

libscramjet_la_SOURCES = comprange.c
# Version of shared library API
libscramjet_la_LDFLAGS = -version-info 0:0:0

check_PROGRAMS = scramjet_test
TESTS          = scramjet_test

# Test program
libscramjet_test_SOURCES  = test.c
libscramjet_test_LDADD    = libscramjet.la
