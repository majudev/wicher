AC_INIT([Wicher], [2.3], [maju@debian])
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])
AC_CONFIG_MACRO_DIR([m4])
AX_BOOST_BASE([1.58])
AX_BOOST_THREAD
AX_BOOST_SYSTEM
AC_PROG_CXX
CHECK_HPDF
AC_CONFIG_HEADERS([config.h])
PKG_CHECK_MODULES([gtkmm3], [gtkmm-3.0])
PKG_CHECK_MODULES([jansson], [jansson])
AC_CONFIG_FILES([
	Makefile
	src/Makefile
	src/server/Makefile
])
AC_OUTPUT
