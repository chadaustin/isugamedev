#!/bin/sh

wget --directory-prefix tmp http://isugamedev.sourceforge.net/midworld/data/resources.zip
mkdir -p build
(cd build && unzip ../tmp/resources.zip)
rm -f tmp/resources.zip

# Remove the directory if it's not empty
FILES=`ls tmp`
if test "x$FILES" = "x"; then
   rmdir tmp
fi
