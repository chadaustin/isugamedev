#ifndef __CAMERA_H__
#define __CAMERA_H__

class Camera
{
public:

	Camera()
	{
		for(int i = 0; i < 3; i++)
		{
			rotate[i] = 0.0;
			trans[i] = 0.0;
		}

		eye[0] = 10.0;
		eye[1] = 0.0;
		eye[2] = 3.0;
	}

	~Camera()
	{

	}

	void XRotate(float Angle)
	{	rotate[0] += Angle;}
	void YRotate(float Angle)
	{	rotate[1] += Angle;}
	void ZRotate(float Angle)
	{	rotate[2] += Angle;}

	void SetXRotate(float Angle)
	{	rotate[0] = Angle; }
	void SetYRotate(float Angle)
	{	rotate[1] = Angle; }
	void SetZRotate(float Angle)
	{	rotate[2] = Angle; }

	void XTrans(float Trans)
	{	trans[0] += Trans;}
	void YTrans(float Trans)
	{	trans[1] += Trans;}
	void ZTrans(float Trans)
	{	trans[2] += Trans;}

	void SetEyeZPosition(float TheEye)
	{	eye[0] = TheEye;}
	void SetEyeYPosition(float TheEye)
	{	eye[1] = TheEye;}
	void SetEyeXPosition(float TheEye)
	{	eye[2] = TheEye;}

	void Process()
	{
		gluLookAt(eye[0], eye[1], eye[2],
  		           0.0, 0.0, 0.0,
			       0.0, 0.0, 1.0);
		glTranslatef(eye[0], eye[1], 0.0);
		glRotatef(rotate[0], 1.0, 0.0, 0.0);
		glRotatef(rotate[1], 0.0, 1.0, 0.0);
		glRotatef(rotate[2], 0.0, 0.0, 1.0);
		glTranslatef(trans[0],trans[1], trans[2]);
	}
private:
	float rotate[3];
	float trans[3];
	float eye[3];
};
#endif

