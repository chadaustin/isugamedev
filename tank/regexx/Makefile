SRCS = maketables.c get.c study.c pcre.c \
	regexx.cc split.cc

PROJECT_NAME = regexx
MK_DIR = ../mk
include $(MK_DIR)/mk.hosttype
include $(MK_DIR)/mk.platform

CXX_FLAGS = $(CXX_SHARED_FLAGS)
include $(MK_DIR)/mk.objs

INCLUDE_PATHS = -I.

all:
	$(MAKE) regexx CXX_FLAGS='$(CXX_SHARED_FLAGS)'
	$(MAKE) testapp CXX_FLAGS='$(CXX_STATIC_FLAGS)'

regexx: $(OBJS)
	$(SO_LINKER) $(SO_FLAGS) $(OBJS) $(OUTPUT_LIB_FLAG) $(LIB_FILENAME)

testapp:
	$(EXE_LINKER) $(EXE_FLAGS) $(INCLUDE_PATHS) testregexx.cc $(OUTPUT_EXE_FLAG) testregexx$(EXE_FILE_SUFFIX) -L. -lregexx

clean:
	-rm $(OBJS)
	-rm -r ii_files
	-rm $(LIB_FILENAME)
	-rm testregexx$(EXE_FILE_SUFFIX)
