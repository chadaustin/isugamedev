#!/bin/sh

# repository:  :pserver:anonymous@pyrallis.aegisknight.org://pyrallis/cvsroot
# password:    <nothing>
# module:      midworld-resources
#
# If aegis has given you a user account on the CVS server, you may use it
# instead


# checkout the resources from aegis's server
cvs -d :pserver:anonymous@pyrallis.aegisknight.org://pyrallis/cvsroot \
    checkout -d resources midworld-resources

# install them into the build directory
cd resources
sh install.sh ../build
