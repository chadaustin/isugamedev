SOURCES =					\
	src/Client.java				\
	src/ClientFrame.java			\
	src/ConnectionThread.java		\
	src/NavigationBehavior.java		\
	src/NavigationListener.java		\
	src/Server.java				\
	src/ServerConnection.java		\
	src/SynchronizationBehavior.java	\
	src/Packet.java				\
	src/WorldPacket.java

JAVAC = javac -deprecation -d .

all: dbg

opt:
	$(JAVAC) -O $(SOURCES)

dbg:
	$(JAVAC) -g $(SOURCES)

.PHONY: all opt dbg
