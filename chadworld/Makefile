SOURCES = \
	Client/ChadWorldClient.java \
	Client/ServerConnection.java \
	Common/Packet.java \
	Server/ChadWorldServer.java \
	Server/ConnectionThread.java

JAVAC = javac -deprecation -d .

all: dbg

opt:
	$(JAVAC) -O $(SOURCES)

dbg:
	$(JAVAC) -g $(SOURCES)

.PHONY: all opt dbg
