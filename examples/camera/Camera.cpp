#include "Camera.h"
#include "Vec3.h"
#include "Matrix4f.h"
#include <math.h>


#define PI 3.1415926535

camera::camera(){
	mat.makeIdent();
	xzRot=0;

}

camera::~camera(){


}
 

void camera::setPos(float vec[]){
	mat.setTrans(vec);
}

void camera::setPos(Vec3<float> vec){
	mat.setTrans(vec);
}


void camera::setPos(float x, float y, float z){
	mat.setTrans(x, y, z);
	
}

void camera::set(Matrix4f m){
	mat.copyTrans(m);
}

void camera::setTilt(float tilt){
	
	// convert tilt to radians
	float tiltInRad = tilt/180*PI;
	Vec3<float> vec;	// axis to rotate around, it is the cross product of 
						// the Vup with the direction the camera is pointing 
						// currently in the xz plane
	
	Vec3<float> yax;	// TODO: change this from yaxis to arbitrary up axis
	Vec3<float> dir;
	mat.getTrans(dir);
	yax[0]=0;
	yax[1]=1;
	yax[2]=0;
	// now get the cos of the rotation angle around y from mat
//	float r0,r1;
//	r0 = mat.data()[0]; // cos(a)
//	r1 = mat.data()[8]; // sin(a)

	dir[0] = sin(xzRot*PI/180);
	dir[1] = 0;
	dir[2] = cos(xzRot*PI/180);

	
	
	// now do cross product calculation yax x dir = vec
	

	vec[0] = yax[1]*dir[2] - yax[2]*dir[1];
	vec[1] = yax[2]*dir[0] - yax[0]*dir[2];
	vec[2] = yax[0]*dir[1] - yax[1]*dir[0];
	
	std::cout << vec << std::endl;
	std::cout << yax << std::endl;
	std::cout << dir << std::endl << std::endl;
	
	
	// now rotate around this vector by tiltInRad
	
	Matrix4f temp, final;
	temp.makeIdent();
	temp.rotate(tiltInRad, vec);
	std::cout << "temp: " << std::endl;
	std::cout << temp << std::endl << std::endl;
	temp.multiply(final, temp,mat);
	mat.set(final);
	

}

void camera::spin(float rot){
	rot=rot/180*PI;
	Matrix4f temp,final;
	temp.makeIdent();
	temp.rotateY(rot);
	temp.multiply(final, temp, mat);
	mat.set(final);
	xzRot +=rot;

}

void camera::spin(float rot, float x, float y, float z){
	rot=rot/180*PI;
	Matrix4f temp, final;
	temp.makeIdent();
	temp.rotate(rot, x, y, z);
	temp.multiply(final, temp, mat);
	mat.set(final);
	xzRot += rot;
}
