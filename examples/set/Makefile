HOSTTYPE:=$(shell uname)

# standardize on the names: linux, irix

# linux
ifeq ($(HOSTTYPE), Linux)
HOSTTYPE=linux
endif

# irix
ifeq ($(HOSTTYPE), IRIX64)
HOSTTYPE=irix
endif

ifeq ($(HOSTTYPE), IRIX)
HOSTTYPE=irix
endif

## build it...

SRCS = simpleGlutApp.cpp 

ifeq ($(HOSTTYPE), irix)
all:
	CC $(SRCS) -o lr -lglut -lGL -lGLU -lX11 -lXmu
endif

ifeq ($(HOSTTYPE), linux)
all:
	g++ $(SRCS) -o lr -lglut -lGL -lGLU -L/usr/X11R6/lib -lX11 -lXmu
endif


