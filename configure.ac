AC_INIT([libsamsung-ipc], [0.1.0], [smartphones-userland@linuxtogo.org], [libsamsung-ipc])
AC_CONFIG_SRCDIR([Makefile.am])
AC_CONFIG_HEADERS(config.h)
AM_INIT_AUTOMAKE([dist-bzip2 subdir-objects])
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
# protocol version we're building for

AC_ARG_WITH(protocol-version, [  --with-protocol-version=NAME     Version of the IPC protocol we're building libsamsung-ipc for],
            [v=$withval;protocol_version=$v], [protocol_version=crespo])
AM_CONDITIONAL([WANT_PROTOCOL_VERISON_CRESPO], [test x"$protocol_version" = x"crespo"])
AM_CONDITIONAL([WANT_PROTOCOL_VERISON_H1], [test x"$protocol_version" = x"h1"])

#------------------------------------------------------------------------------
# openssl

PKG_CHECK_MODULES(OPENSSL, openssl >= $OPENSSL_REQUIRED)
AC_SUBST(OPENSSL_CFLAGS)
AC_SUBST(OPENSSL_LIBS)

#------------------------------------------------------------------------------
# check for debugging
AC_ARG_ENABLE(debug,
  [  --enable-debug            Enable debug build (default=disabled)],
  [debug=$enableval],
  [debug="no"])
AM_CONDITIONAL( [WANT_DEBUG], [test x"$debug" = x"yes"])


#------------------------------------------------------------------------------
# git version
GITV=`cat .git/refs/heads/master || echo "unknown"`
AC_DEFINE_UNQUOTED([PACKAGE_GITV], ["${GITV}"], [git version])

#------------------------------------------------------------------------------

AC_CONFIG_FILES([
    Makefile
    samsung-ipc-1.0.pc
    include/Makefile
    samsung-ipc/Makefile
    tools/Makefile
])
AC_OUTPUT

#------------------------------------------------------------------------------
# info

echo
echo
echo
echo "------------------------------------------------------------------------"
echo "$PACKAGE_NAME $PACKAGE_VERSION-$GITV"
echo "------------------------------------------------------------------------"
echo
echo "Configuration Options:"
echo
echo "  protocol version........: $protocol_version"
echo
echo "  debug build.............: $debug"
echo
echo "  prefix..................: $prefix"
echo
echo "------------------------------------------------------------------------"
echo
echo "Now type 'make' to compile and 'make install' to install this package."

