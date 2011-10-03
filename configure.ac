AC_INIT([libsamsung-ipc], [0.1.0], [smartphones-userland@linuxtogo.org], [libsamsung-ipc])
AC_CONFIG_SRCDIR([Makefile.am])
AC_CONFIG_HEADERS(config.h)
AM_INIT_AUTOMAKE([dist-bzip2])
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

AC_PROG_CC
AM_PROG_CC_C_O
AC_GNU_SOURCE
AC_DISABLE_STATIC
AC_PROG_LIBTOOL

AC_SUBST(CFLAGS)
AC_SUBST(CPPFLAGS)
AC_SUBST(LDFLAGS)

OPENSSL_REQUIRED=0.0.0

#------------------------------------------------------------------------------
# pkg-config

PKG_PROG_PKG_CONFIG

#------------------------------------------------------------------------------
# openssl

PKG_CHECK_MODULES(OPENSSL, openssl >= OPENSSL_REQUIRED)
AC_SUBST(OPENSSL_CFLAGS)
AC_SUBST(OPENSSL_LIBS)

#------------------------------------------------------------------------------

AC_CONFIG_FILES([
	Makefile
	samsung-ipc-1.0.pc
	include/Makefile
	samsung-ipc/Makefile
])
AC_OUTPUT
