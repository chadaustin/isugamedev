#include "player.h"
#include "level.h"

class badguy : public player	// this maybe isn't a very good idea to inherit 
								// publically here, but I'm going to do it to save 
								// time
{
public:
	void initTexture();
	badguy(int Pheight, int Ppos, int Pstate, bool fall){
		height = Pheight;
		pos = Ppos;
		state = Pstate;
		falling = fall;
		texState =0;
	}
	void findPlayer(player p);
	void findLadder(level l);
	void goToTarget(int pos);
	void update();
public:
	int targetPos;
	int targetHeight;
	int playerPos;
	int playerHeight;
	bool usingtarget;
};