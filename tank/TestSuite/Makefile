
###############################################################################$
# builder for test suite.  uses kevin's build system in @srcdir@/mk
###############################################################################$

# project name...
PROJECT_NAME = runner.exe

default: $(PROJECT_NAME)

PATH_TO_SRCS = .:..:CppUnit:CppUnit/framework:CppUnit/textui
INCLUDE_PATHS = -I. -I.. -ICppUnit -ICppUnit/framework -ICppUnit/textui
CPPUNIT_TEXTUI_SRCS = TestRunner.cpp TextTestResult.cpp
CPPUNIT_SRCS = TestCase.cpp \
               TestResult.cpp \
               TestFailure.cpp \
               TestSuite.cpp
RUNNER_SRCS = main.cpp
SRCS    := $(TEST_SRCS) $(CPPUNIT_TEXTUI_SRCS) $(CPPUNIT_SRCS) $(RUNNER_SRCS)
LIBS = -lm

MK_DIR = ../mk

include ${MK_DIR}/mk.hosttype
include ${MK_DIR}/mk.platform
include ${MK_DIR}/mk.objs

# Compile then Link
$(PROJECT_NAME): $(OBJS)
	@echo ""
	@echo "-------------------------------------------"
	@echo "Linking... (.$(OBJEXT)'s --> executable)"
	@echo "-------------------------------------------"
	$(EXE_LINKER) $(EXE_FLAGS) ${OBJS} $(OUTPUT_EXE_FLAG)$(EXE_FILENAME) $(LIB_PATHS) $(LIBS)
	@echo ""
	@echo "-------------------------------------------"
	@echo "$(PROJECT_NAME) done"
	@echo "-------------------------------------------"

# Remove the compiled stuff from the system
clean:
	@echo ""
	@echo "-------------------------------------------"
	@echo "Removing compiled stuff from the system   "
	@echo "-------------------------------------------"
	rm -fr $(OBJS) $(PROJECT_NAME) *.ncb *.opt *.plg *.ilk *.idb    \
	  *.pdb *.pch Debug/ Release/ ii_files/ *core

clobber: clean
	rm -f *.d

include ${MK_DIR}/mk.depend



