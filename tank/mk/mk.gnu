# gnu compiler defines 
CC = g++
CXX_COMPILE = g++
CXX_FLAGS = 
C_COMPILE = gcc
C_FLAGS = $(CXX_FLAGS)
EXE_LINKER = $(CXX_COMPILE)
EXE_FLAGS = 
SO_LINKER = $(CXX_COMPILE)
SO_FLAGS = -dynamic -fPIC
DEFS =
WARNINGS_FLAGS = 

OBJ_FILE_SUFFIX = o
EXE_FILE_SUFFIX=
LIB_FILE_SUFFIX = so

FILENAME = $(PROJECT_NAME)
LIB_FILENAME = lib$(PROJECT_NAME).so

OUTPUT_EXE_FLAG = -o
OUTPUT_OBJ_FLAG = -c -o
OUTPUT_LIB_FLAG = -o

