## Source directory

h_sources  = CondVar.h File.h InetAddress.h Socket.h ServerSocket.h Timer.h Mutex.h Stream.h Thread.h Util.h Directory.h string.h Buffer.h Digest.h DatagramSocket.h DatagramPacket.h DOMNode.h XML.h StringTokenizer.h NonCopyable.h Runnable.h Waitable.h Lockable.h
cpp_sources = CondVar.cpp Mutex.cpp InetAddress.cpp ServerSocket.cpp Stream.cpp Thread.cpp File.cpp Socket.cpp Timer.cpp Directory.cpp string.cpp Buffer.cpp Digest.cpp DatagramSocket.cpp DatagramPacket.cpp DOMNode.cpp XML.cpp StringTokenizer.cpp md5.c sha1.c crc64.c sha2.c

noinst_LTLIBRARIES = libUtil.la
libUtil_la_SOURCES = $(h_sources) $(cpp_sources)

library_includedir=$(includedir)/CDL/Util
library_include_HEADERS = $(h_sources)

DEFAULT_INCLUDES = -I$(top_srcdir)

EXTRA_DIST=md5.c md5.h sha1.c sha1.h crc64.c crc64.h sha2.h
.SILENT:
