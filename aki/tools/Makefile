
CPP_EXTS = java,h.in,h,cxx,cpp
HASH_EXTS = in,sh

default: usage
usage:
	@echo ""
	@echo "Usage:"
	@echo "     make [all|gk]"
	@echo ""

all: gk

gk:
	auto-copyright.pl -d ../ -e $(CPP_EXTS) -c gk-heading.c.txt  -t gk-heading-replace.c.pl -a
	auto-copyright.pl -d ../ -e $(HASH_EXTS) -c gk-heading.hash.txt -t gk-heading-replace.hash.pl -a
