
CPP_EXTS = java,h.in,h,cxx,cpp
HASH_EXTS = in,pl,sh

default: usage
usage:
	@echo ""
	@echo "Usage:"
	@echo "     make [copyright|heading|all]"
	@echo ""

all: copyright heading

# All the projects
copyright:
	auto-copyright.pl -d ../../phui -e $(CPP_EXTS) -c data/phui-copyright.c.txt  -t config/phui-copyright-replace.c.pl -a
	auto-copyright.pl -d ../../phui -e $(HASH_EXTS) -c data/phui-copyright.hash.txt -t config/phui-copyright-replace.hash.pl -a
	auto-copyright.pl -d ../../examples -e $(CPP_EXTS) -c data/phui-copyright.c.txt  -t config/phui-copyright-replace.c.pl -a
	auto-copyright.pl -d ../../examples -e $(HASH_EXTS) -c data/phui-copyright.hash.txt -t config/phui-copyright-replace.hash.pl -a

heading:
	auto-copyright.pl -d ../../phui -e $(CPP_EXTS) -c data/phui-heading.c.txt  -t config/phui-heading-replace.c.pl -a
	auto-copyright.pl -d ../../phui -e $(HASH_EXTS) -c data/phui-heading.hash.txt -t config/phui-heading-replace.hash.pl -a
	auto-copyright.pl -d ../../examples -e $(CPP_EXTS) -c data/phui-heading.c.txt  -t config/phui-heading-replace.c.pl -a
	auto-copyright.pl -d ../../examples -e $(HASH_EXTS) -c data/phui-heading.hash.txt -t config/phui-heading-replace.hash.pl -a

