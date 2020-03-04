dnl Copyright (c) 2000, Red Hat, Inc.

dnl
dnl     This program is free software; you can redistribute it and/or modify
dnl     it under the terms of the GNU General Public License as published by
dnl     the Free Software Foundation; either version 2 of the License, or
dnl     (at your option) any later version.

dnl
dnl     A copy of the GNU General Public License can be found at
dnl     http://www.gnu.org/

dnl
dnl Written by Christopher Faylor <cgf@redhat.com>
dnl and Robert Collins  <rbtcollins@hotmail.com>
dnl
dnl $Id: configure.in,v 2.19 2013/08/24 12:55:49 briand Exp $
dnl
dnl Autoconf configure script for Cygwin utilities.
dnl
dnl Process this file with autoconf to produce a configure script.


AC_INIT([setup], [0], [osgeo4w-dev@lists.osgeo.org])
AC_PREREQ([2.60])
AC_CONFIG_AUX_DIR([cfgaux])
AM_INIT_AUTOMAKE([1.12 subdir-objects foreign no-define -Wall -Wno-portability])
dnl AM_CONFIG_HEADER(include/autoconf.h)
m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES(yes)])
AC_CONFIG_SRCDIR([Makefile.in])
AC_REVISION($Revision: 2.32 $)dnl


AC_MSG_CHECKING([Whether to build inilint])
AC_ARG_ENABLE(inilint,
	    AS_HELP_STRING([--enable-inilint],[Build the inilint tool]),


	    ac_cv_enable_inilint=$enableval, ac_cv_enable_inilint=no)
AC_MSG_RESULT([$ac_cv_enable_inilint])
if test $ac_cv_enable_inilint = yes; then
  INILINT="inilint\$(EXEEXT)"
else
  INILINT=
fi
AC_SUBST(INILINT)

AC_ARG_ENABLE(mirror,
    AC_HELP_STRING([--enable-mirror=URL],
        [ osgeo4w mirror to use, '--enable-mirror=http://download.osgeo.org/osgeo4w/testing64']),

    [ AC_DEFINE_UNQUOTED([OSGEO4W_MIRROR_URL], ["$enableval"], [configured mirror url]) ],
    [ AC_MSG_ERROR([*** osgeo4w mirror undefined.]) ]
)


AC_LANG_CPLUSPLUS
AC_PROG_CXX
AM_PROG_CC_C_O
AM_PROG_LEX
AC_PROG_YACC
AC_CANONICAL_BUILD
AC_CANONICAL_HOST
AC_PROG_LIBTOOL

dnl AC_CHECK_TOOL(AR, ar, ar)
dnl AC_SUBST(AR)
dnl AC_CHECK_TOOL(AS, as, as)
dnl AC_SUBST(AS)
dnl AC_CHECK_TOOL(RANLIB, ranlib, ranlib)
dnl AC_SUBST(RANLIB)
dnl AC_CHECK_TOOL(LD, ld, ld)
dnl AC_SUBST(LD)
dnl AC_CHECK_TOOL(DLLTOOL, dlltool, dlltool)
dnl AC_SUBST(DLLTOOL)
AC_CHECK_TOOL(WINDRES, windres, windres)
AC_SUBST(WINDRES)
dnl AC_CHECK_TOOL(OBJCOPY, objcopy, objcopy)
dnl AC_SUBST(OBJCOPY)


AC_CHECK_HEADERS(alloca.h \
		 errno.h \
		 string \
		 string.h )


AC_CHECK_HEADER(zlib.h, , missing_deps="$missing_deps zlib")
AC_CHECK_HEADER(bzlib.h, , missing_deps="$missing_deps libbz2")





if test -n "$missing_deps"; then
	AC_MSG_ERROR([missing prerequisites: $missing_deps])
fi

prefix=`pwd`/inst; mkdir -p "$prefix"
exec_prefix=$prefix
ac_configure_args="$ac_configure_args --disable-shared"
AC_CONFIG_SUBDIRS(libgetopt++)

dnl add portability sources to inilint
case "$host" in
i?86-*-mingw32)
  SETUP="osgeo4w-setup-x86"
  ;;
x86_64-*-mingw32)
  SETUP="osgeo4w-setup-x86_64"
  ;;
*)
  AC_MSG_ERROR([OSGeo4W cannot be built for $host])
  ;;
esac
AC_SUBST(SETUP)

AC_CONFIG_FILES([Makefile tests/Makefile])
AC_OUTPUT

