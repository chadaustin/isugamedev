
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
	auto-copyright.pl -d ../../client -e $(CPP_EXTS) -c data/brotha-copyright.c.txt  -t config/brotha-copyright-replace.c.pl -a
	auto-copyright.pl -d ../../client -e $(HASH_EXTS) -c data/brotha-copyright.hash.txt -t config/brotha-copyright-replace.hash.pl -a
	auto-copyright.pl -d ../../game -e $(CPP_EXTS) -c data/brotha-copyright.c.txt  -t config/brotha-copyright-replace.c.pl -a
	auto-copyright.pl -d ../../game -e $(HASH_EXTS) -c data/brotha-copyright.hash.txt -t config/brotha-copyright-replace.hash.pl -a
	auto-copyright.pl -d ../../net -e $(CPP_EXTS) -c data/brotha-copyright.c.txt  -t config/brotha-copyright-replace.c.pl -a
	auto-copyright.pl -d ../../net -e $(HASH_EXTS) -c data/brotha-copyright.hash.txt -t config/brotha-copyright-replace.hash.pl -a
	auto-copyright.pl -d ../../thread -e $(CPP_EXTS) -c data/brotha-copyright.c.txt  -t config/brotha-copyright-replace.c.pl -a
	auto-copyright.pl -d ../../thread -e $(HASH_EXTS) -c data/brotha-copyright.hash.txt -t config/brotha-copyright-replace.hash.pl -a

heading:
	auto-copyright.pl -d ../../brotha -e $(CPP_EXTS) -c data/brotha-heading.c.txt  -t config/brotha-heading-replace.c.pl -a
	auto-copyright.pl -d ../../brotha -e $(HASH_EXTS) -c data/brotha-heading.hash.txt -t config/brotha-heading-replace.hash.pl -a
	auto-copyright.pl -d ../../game -e $(CPP_EXTS) -c data/brotha-heading.c.txt  -t config/brotha-heading-replace.c.pl -a
	auto-copyright.pl -d ../../game -e $(HASH_EXTS) -c data/brotha-heading.hash.txt -t config/brotha-heading-replace.hash.pl -a
	auto-copyright.pl -d ../../net -e $(CPP_EXTS) -c data/brotha-heading.c.txt  -t config/brotha-heading-replace.c.pl -a
	auto-copyright.pl -d ../../net -e $(HASH_EXTS) -c data/brotha-heading.hash.txt -t config/brotha-heading-replace.hash.pl -a
	auto-copyright.pl -d ../../thread -e $(CPP_EXTS) -c data/brotha-heading.c.txt  -t config/brotha-heading-replace.c.pl -a
	auto-copyright.pl -d ../../thread -e $(HASH_EXTS) -c data/brotha-heading.hash.txt -t config/brotha-heading-replace.hash.pl -a

