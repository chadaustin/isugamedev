CLASSES = \
	BallObject \
	BlockObject \
	BMPLoader \
	BulletObject \
	collisiondetection \
	GameWorld \
	PaddleObject \
	PowerupObject \
	WallObject

SRCS = \
	Breakout.cpp

OBJS = $(addsuffix .o, $(CLASSES))
OBJS += $(SRCS:.cpp=.o)

breakout: $(OBJS)
	c++ $(OBJS) -lglut -lGLU -lGL -o $@

%.o: %.cpp
	c++ -o $@ -c $<
