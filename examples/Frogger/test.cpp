#include <iostream.h>
#include "collisiondetection.h"
#include "MyObject.h"
#include "FrogObject.h"

enum Movement{NONE = 0, LEFT, RIGHT, UP, DOWN} FrogMove;

int main()
{
	MyObject* Frog1 = new FrogObject;
	MyObject* Frog2 = new FrogObject;
	MyObject* Frog3 = new FrogObject;
	MyObjectStore* Collisions;
	int NumCollisions = 0;

	CollisionDetection MyPond;

	Frog1->SetGameCoordinates(30,30);
	Frog1->SetSize(30,30);

	Frog2->SetGameCoordinates(50,100);
	Frog2->SetSize(30,30);

	Frog3->SetGameCoordinates(80,300);
	Frog3->SetSize(30,30);

	if (MyPond.AddObject(Frog1))
		cout << "Frog1 in Pond" << endl;

	if (MyPond.AddObject(Frog2))
		cout << "Frog2 in Pond" <<endl;

	if (MyPond.AddObject(Frog3))
		cout << "Frog3 in Pond" << endl;

	cout << MyPond;

	MyPond.RemoveObject(Frog2);

	cout << endl << "After Remove" << endl;
	cout << MyPond;

	MyPond.Move(Frog1, 200, 80);
	cout << endl << "After Move" << endl;
	cout << MyPond;

	MyPond.Move(Frog1, 90, 200);
	cout << endl << "After Move" << endl;
	cout << MyPond;

	if(MyPond.CheckForCollisions(Collisions, NumCollisions))
		cout << "Collision Found" << endl;

	return 0;
}



