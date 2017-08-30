AC_INIT([Wicher], [2.3.2], [maju@majudev.net])
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])
AC_CONFIG_MACRO_DIR([m4])
AX_BOOST_BASE([1.58])
AX_BOOST_THREAD
AX_BOOST_SYSTEM
AC_PROG_CC
AC_PROG_CXX
CHECK_HPDF
AC_CONFIG_HEADERS([buildconfig.h])
PKG_CHECK_MODULES([gtk3], [gtk+-3.0])
PKG_CHECK_MODULES([jansson], [jansson])

AC_CHECK_HEADERS([winsock2.h], [USE_WINSOCK=1], [USE_WINSOCK=0])
AC_CHECK_LIB([ws2_32], [WSACleanup])
AM_CONDITIONAL([USE_WINSOCK], [test "$ac_cv_lib_ws2_32_WSACleanup" = "yes"])

AC_CONFIG_FILES([
	Makefile
	src/Makefile
	src/server/Makefile
])
AC_OUTPUT
