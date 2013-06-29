# gcc -O3 -lgsl -fopenmp -std=c99 -march=native -Wall -I../../../include index.c comprange.c -o index && ./index
AC_INIT([scramjet], [0.1], [lists@alesjosanchez.com])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AC_PROG_CC
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile src/Makefile])
LT_INIT

AC_CONFIG_MACRO_DIR([m4])
AC_CHECK_FUNCS([gettimeofday])
AC_CHECK_FUNCS([strtol])
AC_CHECK_HEADERS([sys/time.h])
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_PROG_CXX
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T

AC_OUTPUT
