SDL_CFLAGS := $(shell sdl-config --cflags)
SDL_LDFLAGS := $(shell sdl-config --libs)

Frogger : AutoObject.o collisiondetection.o FrogObject.o GameWorld.o LilypadObject.o LogObject.o
	g++ -o Frogger Frogger.cpp AutoObject.o collisiondetection.o FrogObject.o GameWorld.o LilypadObject.o LogObject.o $(SDL_CFLAGS) $(SDL_LDFLAGS) -L/usr/X11R6/lib -lGL -lGLU

AutoObject.o : AutoObject.cpp
	g++ -c AutoObject.cpp $(SDL_CFLAGS) 
collisiondetection.o : collisiondetection.cpp
	g++ -c collisiondetection.cpp
FrogObject.o : FrogObject.cpp
	g++ -c FrogObject.cpp $(SDL_CFLAGS)
GameWorld.o : GameWorld.cpp
	g++ -c GameWorld.cpp $(SDL_CFLAGS)
LilypadObject.o : LilypadObject.cpp
	g++ -c LilypadObject.cpp $(SDL_CFLAGS)
LogObject.o : LogObject.cpp
	g++ -c LogObject.cpp $(SDL_CFLAGS)

