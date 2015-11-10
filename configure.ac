dnl
dnl   Configure script for the SICOM Systems libphpscrew module
dnl   Copyright (c) 2015 SICOM Systems Inc (zboszormenyi@sicompos.com)
dnl

dnl init autoconf
AC_INIT([libphpscrew],[1.5.0],[http://www.sicom.com])
AC_DEFINE(VERSION_TITLE,["RELEASE"],[Release Title])
AC_PREREQ([2.50])
AC_CONFIG_SRCDIR(config.h.in)
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR(.)

AM_INIT_AUTOMAKE()
AC_CONFIG_HEADERS(config.h)
AM_MAINTAINER_MODE

AC_LIB_RPATH
AC_PROG_CC
AC_PROG_AWK
AC_PROG_INSTALL
AC_PROG_MAKE_SET
AC_PROG_LN_S
AM_PROG_CC_C_O
AM_PROG_AR
LT_INIT([shared])
LT_OUTPUT

dnl
dnl Libtool's versioning system can be read at
dnl http://www.gnu.org/software/libtool/manual/html_node/Libtool-versioning.html
dnl The number triplet is CURRENT:REVISION:AGE, the library
dnl can provide several interface versnios, represented by "CURRENT" and "AGE".
dnl The interface versions CURRENT-AGE, ..., CURRENT are supported by the library,
dnl with "REVISION" being the revision of the CURRENT interface version.
dnl The "CURRENT" and "AGEe" are also encoded in the library version.
dnl Some examples:
dnl -version-info 1:0:0 -> libXXX.so.1.0.0, supports interface version 1
dnl -version-info 1:3:0 -> libXXX.so.1.0.3, supports interface version 1, rev 3
dnl -version-info 2:0:1 -> libXXX.so.1.1.0, supports interface version 1 & 2
dnl -version-info 2:3:1 -> libXXX.so.1.1.3, supports interface version 1 & 2, rev 3
dnl -version-info 2:3:0 -> libXXX.so.2.0.3, supports interface version 2, rev 3
dnl
LIBPHPSCREW_CURRENT=6
LIBPHPSCREW_REVISION=0
LIBPHPSCREW_AGE=5

AC_SUBST(LIBPHPSCREW_CURRENT)
AC_SUBST(LIBPHPSCREW_REVISION)
AC_SUBST(LIBPHPSCREW_AGE)

AC_TRY_LINK_FLAG([-Wl,--no-undefined],[ac_cv_Wl_no_undefined])
AC_TRY_LINK_FLAG([-Wl,-z,defs],[ac_cv_Wl_z_defs])
AC_TRY_LINK_FLAG([-Wl,--as-needed],[ac_cv_Wl_as_needed])
AC_TRY_LINK_FLAG([-Wl,--no-allow-shlib-undefined],[ac_cv_Wl_no_allow_shlib_undefined])
AC_TRY_LINK_FLAG([-Wl,--no-copy-dt-needed-entries],[ac_cv_Wl_no_copy_dt_needed_entries])
AS_IF([test x$ac_cv_Wl_no_copy_dt_needed_entries = xno],
	[AC_TRY_LINK_FLAG([-Wl,--no-add-needed],[ac_cv_Wl_no_add_needed])])

if test x$enable_maintainer_mode = xyes ; then
	WERRORFLAG=
else
	WERRORFLAG="-Werror"
fi
AC_SUBST(WERRORFLAG)

gl_VISIBILITY
AS_IF([test x$gl_cv_cc_visibility = xyes],
	[AC_DEFINE(DLL_EXPORT,[__attribute__((visibility("default")))],[Explicitly export global symbol])],
	[AC_DEFINE(DLL_EXPORT,[],[Implicitly export all global symbols])]
)
CFLAGS="$CFLAGS $CFLAG_VISIBILITY $WERRORFLAG"

AC_ARG_WITH([libtool-files],
	[AS_HELP_STRING([--without-libtool-files],
	[do not install libtool libname.la files])],
	[AS_IF([test x$with_libtool_files = xyes],[],[test x$with_libtool_files = xno],[],[AC_MSG_ERROR([--with-libtool-files must not need an argument])])],
	[with_libtool_files=yes])
AM_CONDITIONAL(NO_LA, test x$with_libtool_files = xno)

AC_ARG_WITH([pkgconfigdir],
	[AS_HELP_STRING([--with-pkgconfigdir=<dir>],
		[specify pkgconfig directory @<:@default=${libdir}/pkgconfig@:>@])],
	[AS_IF([test x$with_pkgconfigdir = xyes],
		[AC_MSG_ERROR([--with-pkgconfigdir needs a directory PATH])],
		[pkgconfigdir=$with_pkgconfigdir])],
	[pkgconfigdir=${libdir}/pkgconfig])
AC_SUBST(pkgconfigdir)

PKG_CHECK_MODULES(ZLIB, zlib >= 1.2.8)
AC_SUBST(ZLIB_CFLAGS)
AC_SUBST(ZLIB_LIBS)

AC_CONFIG_FILES([
	libphpscrew.pc
	Makefile
	include/Makefile
	libsrc/Makefile
])
AC_OUTPUT
