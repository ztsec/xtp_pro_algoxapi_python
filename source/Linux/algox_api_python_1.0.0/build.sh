#!/bin/bash

set -e
BUILDDIR=build
rm -rf $BUILDDIR
if [ ! -f $BUILDDIR ]; then
    mkdir -p $BUILDDIR
fi
pushd $BUILDDIR
cmake ..
make VERBOSE=1 -j 1
cp `pwd`/lib/vnxtpalgox.so ../
cp `pwd`/lib/vnxtpalgox.so ../
popd
