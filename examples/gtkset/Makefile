CFLAGS = -g $(DEFS) -Wall
CC = g++
LIBS = -lresolv 
GTKCFLAGS = `gtk-config --cflags`
GTKLIBS =  `gtk-config --libs`
GNOMEFLAGS= `gnome-config --cflags gnomeui`
GNOMELIBS = `gnome-config --libs gnomeui`

all: card.o deck.o table.o set

card.o: card.cpp
	$(CC) $(GNOMEFLAGS) $(GTKCFLAGS) -o $@ -c $<
	
deck.o: deck.cpp
	$(CC) $(GNOMEFLAGS) $(GTKCFLAGS) -o $@ -c $< 

table.o: table.cpp
	$(CC) $(GNOMEFLAGS) $(GTKCFLAGS) -o $@ -c $< 

set: set.cpp
	$(CC) $(GNOMEFLAGS) $(GTKCFLAGS) $(GTKLIBS) $(GNOMELIBS) $(LIBS) -o $@ $< card.o table.o deck.o

clean:
	rm -f *.o
	rm set
