ifeq ($(USE_DEBUG), Y)
DEBUG_FLAGS = -g
endif


# gnu compiler defines 
CC = g++
WARNINGS_FLAGS = 
CXX_COMPILE = g++
CXX_STATIC_FLAGS = $(DEBUG_FLAGS) $(WARNINGS_FLAGS)
CXX_SHARED_FLAGS = $(DEBUG_FLAGS) -fPIC $(WARNINGS_FLAGS)
CXX_FLAGS = $(CXX_STATIC_FLAGS)
C_COMPILE = gcc
C_FLAGS = $(CXX_FLAGS)
EXE_LINKER = $(CXX_COMPILE)
EXE_FLAGS = $(CXX_FLAGS) $(WARNINGS_FLAGS)
SO_LINKER = $(CXX_COMPILE)
SO_FLAGS = -shared -fPIC $(DEBUG_FLAGS) $(WARNINGS_FLAGS)
DEFS =
LIBBITSUF=

LINKALL_ON = -Wl,--whole-archive
LINKALL_OFF = -Wl,--no-whole-archive

OBJ_FILE_SUFFIX = .o
EXE_FILE_SUFFIX =
LIB_FILE_PREFIX = lib
LIB_FILE_SUFFIX = .so

EXE_FILENAME = $(PROJECT_NAME)
LIB_FILENAME = $(LIB_FILE_PREFIX)$(PROJECT_NAME)$(LIB_FILE_SUFFIX)

OUTPUT_EXE_FLAG = -o
OUTPUT_OBJ_FLAG = -c -o
OUTPUT_LIB_FLAG = -o

