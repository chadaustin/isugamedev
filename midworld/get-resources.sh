#!/bin/sh

# checkout the resources from aegis's server
cvs -d :pserver:anonymous@pyrallis.aegisknight.org://pyrallis/cvsroot \
    checkout -d resources midworld-resources

# install them into the build directory
cd resources
./install.sh ../build
