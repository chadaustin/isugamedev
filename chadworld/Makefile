SOURCES = \
	src/Client.java	\
	src/Server.java \

JAVAC = javac -sourcepath src -deprecation -d .

all: dbg

opt:
	$(JAVAC) -O $(SOURCES)

dbg:
	$(JAVAC) -g $(SOURCES)

.PHONY: all opt dbg
