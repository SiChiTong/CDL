#! /bin/sh

# $Id: autodel.sh,v 1.1.1.1 2005/03/06 01:24:30 alcoco Exp $

dir=`echo "$0" | sed 's,[^/]*$,,'`
test "x${dir}" = "x" && dir='.'

if test "x`cd "${dir}" 2>/dev/null && pwd`" != "x`pwd`"
then
    echo "This script must be executed directly from the source directory."
    exit 1
fi

echo "- libtoolize."   && \
rm -f *.pc *.log && \
rm -f config.status && \
rm -f config.guess && \
rm -f config.sub && \
rm -f ltmain.sh && \
echo "- aclocal. " && \
rm -f aclocal.m4 && \
echo "- autoconf." && \
rm -fR autom4te.cache && \
rm -f configure && \
echo "- autoheader." && \
rm -f config.h.in config.h && \
echo "- automake." && \
rm -f depcomp && \
rm -f install-sh && \
rm -f Makefile.in && \
rm -f missing && \
rm -f mkinstalldirs && \
echo "- *.o Makefile.in Makefile .XXdir" && \
find ./ \( -name "*.o" -o -name "Makefile.in" -o -name "Makefile" \) -exec rm \{\} \; && \
find ./ \( -name ".??*" -a -type d \) -not -name ".svn" -exec rm -fR \{\} \; && \
exit 0
