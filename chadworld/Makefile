SOURCES = \
	Client/ChadWorldFrame.java \
	Client/Client.java \
	Client/NavigationBehavior.java \
	Client/NavigationListener.java \
	Client/ServerConnection.java \
	Client/SynchronizationBehavior.java \
	Common/Packet.java \
	Common/WorldPacket.java \
	Server/ChadWorldServer.java \
	Server/ConnectionThread.java

JAVAC = javac -deprecation -d .

all: dbg

opt:
	$(JAVAC) -O $(SOURCES)

dbg:
	$(JAVAC) -g $(SOURCES)

.PHONY: all opt dbg
