#include "Matrix4f.h"
#include "Vec3.h"
#ifdef WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
 
class camera{
public:
	// constructor
	camera();
	
	// destructor
	~camera();

	// update
	void update(){
		glMultMatrixf(mat.data());
	}
	
// gets the current vector position of the camera
	Vec3<float> getPos(){
		Vec3<float> vec;
		mat.getTrans(vec);
		return vec;
	}

// get the current camera matrix

	Matrix4f getMat(){
		return mat;
	}

// setting position based on coordinates in space

	virtual void setPos(Vec3<float> vec);
	virtual void setPos(float vec[3]); 
	virtual void setPos(float x, float y, float z);
	
// setting position based on 4x4 float matrix.
	virtual void set(Matrix4f m);


// changing tilt of camera ie looking up/down
	virtual void setTilt(float tilt);	// zero sets tilt to zero ie looking straight
										// straight ahead
										// positives make the camera look up by tilt degrees
										// negatives make the camera look down by tilt dgrees
 
// rotate camera around verticle axis
	virtual void spin(float rot);		// rotates the camera  in the  horizontal 
										// plane around at it's current position
										// counterclockwise by rot in degrees
					
	virtual void spin(float rot, float x, float y, float z);

private:
	Matrix4f mat;  // matrix to hold camera data
	float xzRot;  // Angle we've rotated through in xz plane

};

