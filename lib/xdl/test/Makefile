
CXX = g++
INCLUDE_PATHS = -I..
SRC_PATHS = ..
SHARED_FLAGS = -shared 
OUTPUT_OBJECT_FLAG = -o
CXXFLAGS = -DUSE_UNIX
LIBS = -ldl
EXE_SUFFIX =
SHARED_SUFFIX =.so

vpath %.cpp $(SRC_PATHS)

default: all
all: dltest dirlist_test$(EXE_SUFFIX)
clean:
	rm -rf dltest dirlist_test$(EXE_SUFFIX) test$(SHARED_SUFFIX) lookup_test$(EXE_SUFFIX)


dltest: test$(SHARED_SUFFIX) lookup_test$(EXE_SUFFIX)



test$(SHARED_SUFFIX):
	$(CXX) $(CXXFLAGS) $(SHARED_FLAGS) $(INCLUDE_PATHS) testModule.cpp $(OUTPUT_OBJECT_FLAG) test$(SHARED_SUFFIX)


lookup_test$(EXE_SUFFIX):
	$(CXX) $(CXXFLAGS) $(INCLUDE_PATHS) lookup_test.cpp $(OUTPUT_OBJECT_FLAG) lookup_test$(EXE_SUFFIX) $(LIBS)
	@echo ""
	@echo "you should do this....   setenv LD_LIBRARY_PATH ."
	@echo ""


dirlist_test$(EXE_SUFFIX):
	$(CXX) $(CXXFLAGS) $(INCLUDE_FLAGS) $(INCLUDE_PATHS) dirlist_test.cpp $(OUTPUT_OBJECT_FLAG) $@
