AC_INIT([Wicher], [2.3], [maju@debian])
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])
AC_CONFIG_MACRO_DIR([m4])
AX_BOOST_BASE([1.58])
AX_BOOST_THREAD
AX_BOOST_SYSTEM
AC_PROG_CXX
CHECK_HPDF
AC_CONFIG_HEADERS([buildconfig.h])
PKG_CHECK_MODULES([gtkmm3], [gtkmm-3.0])
PKG_CHECK_MODULES([jansson], [jansson])

#AC_CANONICAL_HOST

#build_linux=no
#build_windows=no

#AC_MSG_CHECKING([Checking if OS is windows or linux])
# Detect the target system
#case "${host_os}" in
#    linux*)
#        build_linux=yes
#	AC_MSG_RESULT([linux])
#        ;;
#    cygwin*|mingw*)
#        build_windows=yes
#	AC_MSG_RESULT([windows])
#        ;;
#    *)
#        AC_MSG_ERROR(["OS $host_os is not supported"])
#        ;;
#esac

# Pass the conditionals to automake
#AM_CONDITIONAL([LINUX], [test "$build_linux" = "yes"])
#AM_CONDITIONAL([WINDOWS], [test "$build_windows" = "yes"])

AC_CHECK_HEADERS([winsock2.h], [USE_WINSOCK=1], [USE_WINSOCK=0])
AC_CHECK_LIB([ws2_32], [WSACleanup])
AM_CONDITIONAL([USE_WINSOCK], [test "$ac_cv_lib_ws2_32_WSACleanup" = "yes"])
#AM_CONDITIONAL([USE_WINSOCK], [test "$USE_WINSOCK" = 1])

AC_CONFIG_FILES([
	Makefile
	src/Makefile
	src/server/Makefile
])
AC_OUTPUT
