## top directory

SUBDIRS = Image Util Window Math CDTL

h_sources = CDL.h defs.h endian.h
cpp_sources = CDL.cpp

lib_LTLIBRARIES   = libCDL.la
libCDL_la_SOURCES = $(h_sources) $(cpp_sources)
libCDL_la_LDFLAGS = -no-undefined -version-number $(VERSION_INFO) -release $(RELEASE)
libCDL_la_LIBADD  = Image/libImage.la  \
                    Util/libUtil.la    \
		            Math/libMath.la    \
		            Window/libWindow.la \
		            $(LIBRARY_LIBS)

library_includedir=$(includedir)/CDL
library_include_HEADERS = $(h_sources)

INCLUDES = -I$(top_srcdir)
.SILENT:
