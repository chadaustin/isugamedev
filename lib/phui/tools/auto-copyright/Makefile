PROJECT = phui
dirs = ../../phui ../../examples

CPP_EXTS = java,h.in,h,cxx,cpp
HASH_EXTS = in,pl,sh

AUTOCOPYRIGHT = auto-copyright.pl

#------------------------------------------------------------------------------
# You shouldn't have to modify anything past this line.
#------------------------------------------------------------------------------
COPY_DATA_CPP 	= data/$(PROJECT)-copyright.c.txt
COPY_DATA_HASH = data/$(PROJECT)-copyright.hash.txt
COPY_CONFIG_CPP 	= config/$(PROJECT)-copyright-replace.c.pl
COPY_CONFIG_HASH	= config/$(PROJECT)-copyright-replace.hash.pl

HEAD_DATA_CPP 	= data/$(PROJECT)-heading.c.txt
HEAD_DATA_HASH = data/$(PROJECT)-heading.hash.txt
HEAD_CONFIG_CPP 	= config/$(PROJECT)-heading-replace.c.pl
HEAD_CONFIG_HASH	= config/$(PROJECT)-heading-replace.hash.pl

MODELINE_FILE = config/$(PROJECT)-modeline-replace.c.pl

default: usage
usage:
	@echo ""
	@echo "Usage:"
	@echo "     make [copyright|heading|all]"
	@echo ""

all: copyright heading

# All the projects
copyright:
	for d in $(dirs); do \
		$(AUTOCOPYRIGHT) -d $$d -e $(CPP_EXTS) -c $(COPY_DATA_CPP) -t $(COPY_CONFIG_CPP) -a; \
		$(AUTOCOPYRIGHT) -d $$d -e $(HASH_EXTS) -c $(COPY_DATA_CPP) -t $(COPY_CONFIG_CPP) -a; \
	done

heading:
	for d in $(dirs); do \
		$(AUTOCOPYRIGHT) -d $$d -e $(CPP_EXTS) -c $(HEAD_DATA_CPP) -t $(HEAD_CONFIG_CPP) -m $(MODELINE_FILE) -a; \
		$(AUTOCOPYRIGHT) -d $$d -e $(HASH_EXTS) -c $(HEAD_DATA_CPP) -t $(HEAD_CONFIG_CPP) -a; \
	done
