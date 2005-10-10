AC_INIT(CDL/CDL.h)

MAJOR_VERSION=0
MINOR_VERSION=1
MICRO_VERSION=1

LIBRARY_NAME=CDL
LIBRARY_DESC="C++ Development Library"
LIBRARY_PREREQ=""

AC_SUBST(LIBRARY_NAME)
AC_SUBST(LIBRARY_DESC)
AC_SUBST(LIBRARY_PREREQ)

VERSION_INFO=$MAJOR_VERSION:$MINOR_VERSION:$MICRO_VERSION
VERSION=$MAJOR_VERSION.$MINOR_VERSION.$MICRO_VERSION
RELEASE=$MAJOR_VERSION.$MINOR_VERSION

AC_SUBST(VERSION_INFO)
AC_SUBST(VERSION)
AC_SUBST(RELEASE)

AM_INIT_AUTOMAKE($LIBRARY_NAME, $VERSION, no-define, dist-bzip2)

AC_PROG_CXX
AC_LIBTOOL_WIN32_DLL
AM_PROG_LIBTOOL
AC_EXEEXT
AC_CHECK_HEADERS(byteswap.h)
AC_C_BIGENDIAN

case "${host_os}" in
	cygwin*|mingw*|windows*|winnt)
		LIBRARY_LIBS="-lwinmm -lopengl32 -lglu32 -lgdi32 -lwsock32"
		AC_DEFINE([Windows_NT],[],[Windows NT Operating System])
		AC_DEFINE([CDL_EXPORTS],[],[Export all symbols])
	;;
	linux*|solaris*|unix*)
	    LIBRARY_LIBS="-lpthread -lGL -lGLU -L/usr/X11R6/lib -lXxf86vm"
		AC_DEFINE([Linux],[],[POSIX operating system])
	;;
	*)
	    AC_MSG_ERROR([Error no valid os was found])
	;;
esac

AC_SUBST(LIBRARY_LIBS)
AM_CONFIG_HEADER(config.h)
AC_OUTPUT(Makefile CDL.pc CDL/Makefile CDL/Image/Makefile CDL/Util/Makefile
          CDL/Math/Makefile CDL/Window/Makefile CDL/CDTL/Makefile)
