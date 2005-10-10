#! /bin/sh
mkdir /tmp/bindist
make install-strip DESTDIR=/tmp/bindist
tar -C /tmp/bindist -cjvf CDL-bindist.tar.bz2 .
rm -fR /tmp/bindist
