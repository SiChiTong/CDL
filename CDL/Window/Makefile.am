## Source directory

h_sources = Window.h
cpp_sources = Window.cpp

noinst_LTLIBRARIES = libWindow.la
libWindow_la_SOURCES = $(h_sources) $(cpp_sources)

library_includedir=$(includedir)/CDL/Window
library_include_HEADERS = $(h_sources)

DEFAULT_INCLUDES = -I$(top_srcdir)

EXTRA_DIST = winProc.h xwinProc.h toon_root.h
.SILENT:
