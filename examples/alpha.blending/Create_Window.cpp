// Lou Herard
// Unstructured OpenGL Demo
// 4/12/02

/*
	This is sort of a demo on passing in points and colors to glVertex and glColor using arrays
	instead of only user-specified points.  Using this method, you can, for instance, have a
	function calculate the points in a circle or some other weird shape, and pass them into
	opengl on the fly.  It's not very in-depth, but it does cover a few topics that I don't think
	too many tutorials explain very clearly.

	It's also a growing transparency tutorial, even though it's not very helpful yet, but for
	commands to get transparency started, this has enough.  Enjoy.

*/

#include <gl/glut.h>
#include <gl/glu.h>


//---===  GLOBAL VARIABLES   ===---//
int x_angle = 0;
int y_angle = 0;
int z_angle = 0;

float screenW = 800.0;
float screenH = 600.0;


struct Cube
{
	// this code looks weird, but it's a way to specify a struct stored in an array
	struct 
	{
		float point[3];		// create an array of 3 floats: x, y, and z
		float color[4];		// same for color
	} vertex[8];

	struct 
	{
		unsigned int ver[4];		// hold 4 vertices
	} face[6];
};

Cube cube;

void initCube()
{


	float vertexPosData[8][3] =	
	{
		{-10, 10, 10},
		{10, 10, 10},
		{10, -10, 10},
		{-10, -10, 10}, 
		{-10, 10, -10},
		{10, 10, -10},
		{10, -10, -10},
		{-10, -10, -10}
	};		// need the semicolon

/*
	float vertexColData[8][4] =	
	{
		{1.0, 1.0, 1.0, .5},
		{0.0, 1.0, 1.0, .5},
		{0.0, 0.0, 1.0, .5},
		{1.0, 1.0, 0.0, .5},
		{1.0, 0.0, 0.0, .5},
		{0.0, 1.0, 0.0, .5},
		{1.0, 0.0, 1.0, .5},
		{1.0, 1.0, 1.0, .5},
	};
*/
	float vertexColData[8][4] =	
	{
		{1.0, 0.0, 0.0, .7},
		{0.0, 1.0, 0.0, .7},
		{1.0, 0.0, 1.0, .7},
		{1.0, 1.0, 0.0, .7},
		{1.0, 0.0, 0.0, .7},
		{0.0, 1.0, 0.0, .7},
		{0.0, 0.0, 1.0, .7},
		{0.0, 1.0, 0.0, .7},
	};



	unsigned int faceVertexData[6][4] =
	{
		{0,1,2,3},
		{1,5,6,2},
		{5,4,7,6},
		{4,0,3,7},
		{4,5,1,0},
		{7,6,2,3}
	};

	// Data structures 101
	// These loops read the data stored in the arrays defined above

	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (j < 3)
			{
				cube.vertex[i].point[j] = vertexPosData[i][j];
			}
			cube.vertex[i].color[j] = vertexColData[i][j];
		}
	}
	for (i = 0; i < 6; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			cube.face[i].ver[j] = faceVertexData[i][j];
		}
	}
}


void clear()
//clears buffers (screen, depth, etc)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();	// basically clears the transformation matrix
	
	//gluPerspective(view angle, aspect ratio, near clip, far clip
	gluPerspective(45.0, screenW/screenH, 5.0, 160.0);
	
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void draw()

{
	clear();


	glPushMatrix();		// push a matrix onto the stack

	/* Finally, an explanation of this crap!!!  When you call glPushMatrix, it's basically
	like taking a blank sheet of paper and putting on your desk.  You haven't written anything
	on it yet, but it's there, waiting for you to get started. If you call glPushMatrix more than
	once, each matrix it calculates everything relative to the matrix underneath it.  Think of it
	like taking a transparent overhead projector sheet with graph paper grid lines on it.  Pretend
	that the sheet is labeled with numbers, and is centered at some point other than the origin on 
	the projector.  Now, take a blank overhead sheet, also with graph lines drawn on it, but not 
	labeled.  The new overhead is now centered at the same place as the sheet underneath it.  That's
	the long, but short explanation of how glPushMatrix works.*/


	glTranslatef(0.0, 0.0, -100.0);

	glRotatef( (GLfloat) x_angle, 1.0, 0.0, 0.0);
	glRotatef( (GLfloat) y_angle, 0.0, 1.0, 0.0);
	glRotatef( (GLfloat) z_angle, 0.0, 0.0, 1.0);

	/*  Calling glTranslate and glRotate and glTranslate are basically like writing the 
	formulas you're going to use to transform the points that you're going to specify on the
	sheet of paper you put on your desk.  They store the matrix for the transformations specified
	in glTranslate and/or glRotate
*/


// ------======== Beautiful Cubes ========--------
// In order to get alpha blending to work properly, you have to draw the polygons
// from farthest to nearest, which probably means redefining these quads as single polygons
// for each face and then finding the midpoint z value of each face.  Then sorting them (maybe in
// a vector) and then drawing them out like that.  Of course, I didn't do that because I'm too 
// lazy to.  But knowing me, I'll probably have it done soon.


	int currentVertex;

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// This is the line that, I guess, allows fully transparent objects without sorting polygons.  
	// Although, sorting is still the best way to draw because this will make EVERYTHING drawn
	// transparent, so things behind objects that are supposed to be opaque will still be visible.
	// (or at least that's the case according to Kevin)

	glDepthMask(GL_FALSE);



	glBegin(GL_QUADS);

	// (more data structures 101)
	// Get points from arrays
	for (int i = 0; i < 6; ++i)		// quads loop
	{
		for (int j = 0; j < 4; ++j)	// vertex loop
		{
			currentVertex = cube.face[i].ver[j];	//cube's vertex

			glColor4fv (cube.vertex[currentVertex].color);
			glVertex3fv (cube.vertex[currentVertex].point);

			/* Calling glVertex is like actually doing the calculations on the sheet you pulled
			out, and getting the results or the answers.  glVertex calculates the points to
			output to the screen using the transformation matrix, and then outputs them to the
			screen, with the color specified in glColor.  */
		}
	}

		
	glEnd();

	glPopMatrix();

	// you can mess with these values to make the cube spin differently.
	x_angle += 1 % 360;
	y_angle += 3 % 360;
	z_angle += 1 % 360;
}

void render(void)
//render scene
//this function will call any other functions, such as drawbike, drawramp, etc.
{
	draw();

	glutSwapBuffers();//flip buffers.
}


int main(int argc, char **argv)
{
	// Get Cube Stuff
	initCube();
	// Initialize Glut
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_ALPHA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(screenW,screenH);

	glutCreateWindow("Window");


	// Register Callbacks to interact with OS
	glutDisplayFunc(render);
	glutIdleFunc(render);

	// call these after glutCreateWindow()
	glEnable(GL_DEPTH_TEST); 
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glutMainLoop();
	
	return 0;
}


