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

ifeq ($(HOSTTYPE), irix)
all:
	CC vday.cpp -o vday -lglut -lGL -lGLU -lX11 -lXmu -lm
endif

ifeq ($(HOSTTYPE), linux)
all:
	g++ vday.cpp -o vday -lglut -lGL -lGLU -L/usr/X11R6/lib -lX11 -lXmu
endif


