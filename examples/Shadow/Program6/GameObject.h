#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <gl/glut.h>
#include <vector>

using namespace std;

class GameObject
{
public:
	//Microsoft hater says "this won't work in VC6.0 it may work in VC7.0" 
	//	Ben Scott
	//Unix hater won't use Unix where it "WILL" compile"
	//	Levi VanOort
	/*template <int i>
	void Rotate(float Angle)
	{	rotate[i] = Angle; }
	Rotate<1>(20.0);
	*/

	void XRotate(float Angle)
	{	rotate[0] = Angle;}

	void YRotate(float Angle)
	{	rotate[1] = Angle;}

	void ZRotate(float Angle)
	{	rotate[2] = Angle;}

	void XTranslate(float Trans)
	{	translate[0] = Trans;}

	void YTranslate(float Trans)
	{	translate[1] = Trans;}

	void ZTranslate(float Trans)
	{	translate[2] = Trans;}

	void SetColor(float Red, float Blue, float Green)
	{
		color[0] = Red;
		color[1] = Blue;
		color[2] = Green;
	}

	void EnableColor()
	{
		ColorEnabled = true;
	}

	void DisableColor()
	{	ColorEnabled = false;}

	virtual void Draw() = 0;

	float rotate[3];
	float translate[3];
	float scale[3];
	float color[4];
	bool ColorEnabled;
	float TireRotate;

	GameObject* Tires;

	//Used for truck
	float wheelturn;
};
#endif