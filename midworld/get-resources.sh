#!/bin/sh

# repository:  :pserver:anonymous@pyrallis.aegisknight.org://pyrallis/cvsroot
# password:    <nothing>
# module:      midworld-resources
#
# If aegis has given you a user account on the CVS server, you may use it
# instead.  Make a file called resources.cvsroot in the current directory
# and add the CVSROOT to that.  For example:
#
# echo ":pserver:aegis@pyrallis.aegisknight.org:D:/cvsroot" > resources.cvsroot

if [ -f resources.cvsroot ]; then
    CVSROOT=`cat resources.cvsroot`
else
    CVSROOT=:pserver:anonymous@pyrallis.aegisknight.org://pyrallis/cvsroot
fi

echo
echo "Using CVSROOT: $CVSROOT"
echo

# If CVSROOT is different from the CVSROOT used to check out the resources,
# warn and halt.
CO_LOCATION=external
MODULE_NAME=resources
if [ -f $CO_LOCATION/$MODULE_NAME/CVS/Root ] && \
   [ `cat $CO_LOCATION/$MODULE_NAME/CVS/Root` != $CVSROOT ]; then
    echo "CVSROOT does not match previous CVSROOT used to check out resources."
    echo "Remove $CO_LOCATION/$MODULE_NAME and try again."
    exit 1
fi

# Checkout the resources from aegis's server.  Put them in a temporary
# directory so running CVS from this directory doesn't see the
# resources directory and think it should look in there.  (Having files
# from two different repositories in one tree sometimes gives error
# messages.)
INSTALL_FROM=`pwd`
mkdir -p $CO_LOCATION || exit 1
cd $CO_LOCATION || exit 1
cvs -d $CVSROOT checkout -d $MODULE_NAME midworld-resources || exit 1

# install them into the build directory
scons -C $MODULE_NAME TARGET=$INSTALL_FROM/build || exit 1

# install them into the VC7 build directories
scons -C $MODULE_NAME TARGET=$INSTALL_FROM/vc7/midworld/Debug || exit 1
scons -C $MODULE_NAME TARGET=$INSTALL_FROM/vc7/midworld/Release || exit 1
