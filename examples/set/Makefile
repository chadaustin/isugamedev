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

SRCS = simpleGlutApp.cpp BmpImporter.cpp textures.cpp Image.cpp 

ifeq ($(HOSTTYPE), irix)
all:
	CC $(SRCS) -o set-game -lglut -lGL -lGLU -lX11 -lXmu
endif

ifeq ($(HOSTTYPE), linux)
all:
	g++ $(SRCS) -o set-game -lglut -lGL -lGLU -L/usr/X11R6/lib -lX11 -lXmu
endif


