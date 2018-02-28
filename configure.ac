#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([pbp], [0.1])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([src/run.cpp])
AC_CONFIG_HEADERS([config.h:config.h.in])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_INSTALL

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL

# Checks for library functions.

AC_CONFIG_FILES([Makefile:Makefile.in
                 src/Makefile:src/Makefile.in])
AC_OUTPUT
