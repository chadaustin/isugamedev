SRCS = maketables.c get.c study.c pcre.c \
	regexx.cc split.cc

PROJECT_NAME = regexx
MK_DIR = ../mk
include $(MK_DIR)/mk.hosttype
include $(MK_DIR)/mk.platform
include $(MK_DIR)/mk.objs

INCLUDE_PATHS = -I.

all:
	@echo " "
	@echo "==============="
	@echo "Making regexx"
	@echo "==============="
	@echo " "
	$(MAKE) regexx CXX_FLAGS='$(CXX_SHARED_FLAGS)'
	$(MAKE) testapp CXX_FLAGS='$(CXX_STATIC_FLAGS)'

regexx: $(OBJS)
	@echo " "
	@echo "------------------------------------"
	@echo "Making regexx lib ($(LIB_FILENAME))"
	@echo "------------------------------------"
	@echo " "
	$(SO_LINKER) $(SO_FLAGS) $(OBJS) $(OUTPUT_LIB_FLAG)$(LIB_FILENAME)

testapp:
	@echo " "
	@echo "------------------------------------"
	@echo "Making regexx test app (testregexx)"
	@echo "------------------------------------"
	@echo " "
	$(EXE_LINKER) $(EXE_FLAGS) $(INCLUDE_PATHS) testregexx.cc $(OUTPUT_EXE_FLAG) testregexx$(EXE_FILE_SUFFIX) -L. -lregexx

clean:
	-rm $(OBJS)
	-rm -r ii_files
	-rm $(LIB_FILENAME)
	-rm testregexx$(EXE_FILE_SUFFIX)
