// This program is mostly writen by ViperScum, Jason Schneekloth,
// with stupid remarks by Zorloch
// Most of this code for getting a window up and running in windows was learned from
//	the web site nehe.gamedev.net  that place rocks for beginners!


#include <windows.h>
#include <stdio.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>
#include "Tank.h"
#include "Terrain.h"
#include "Bullet.h"
#include "collide.h"


HGLRC		hRC=NULL;			// Permanent Rendering Context
HDC			hDC=NULL;			// Private GDI Device Context
HWND		hWnd=NULL;			// Holds Our Window Handle
HINSTANCE	hInstance;			// Holds The Instance Of The Application


bool keys[256];
bool active = true;
bool fullscreen = true;
GLfloat LightAmbient[]= { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition[]= {-60.0f, 30.0f, -50.0f, 1.0f };
const GLint LEFT = 1;
const GLint RIGHT = -1;
const GLint FORWARD = -1;
const GLint BACK = 1;

GLuint treadTex[14];
GLuint terrainTex[2];
GLuint weaponTex[10];

Tank test(20.0, 0.0, -20.0, 45.0);

Tank test2(-20.0, 0.0, 20.0, -135.0);

Terrain eatMe;

Tank *tank1;
Tank *tank2;


Weapon *tank1Shot;
Weapon *shotCursor;
Weapon *lastShot;

Weapon *tank2Shot;
Weapon *shot2Cursor;
Weapon *lastShot2;

AUX_RGBImageRec *LoadBMP(char *Filename)
{// Loads A Bitmap Image
	FILE *File=NULL;

	if (!Filename)	// Make Sure A Filename Was Given
	{
		return NULL;
	}

	File=fopen(Filename,"r");

	if (File)		// Does The File Exist?
	{
		fclose(File);
		return auxDIBImageLoad(Filename);
	}

	return NULL;
}

int LoadGLTextures()
{
	int Status=false;

	AUX_RGBImageRec *TextureImage[1];
	memset(TextureImage,0,sizeof(void *)*1);

	if (TextureImage[0]=LoadBMP("data/smallTread.bmp"))
	{
		Status=true;
		glGenTextures(1, &treadTex[0]);
		// Create top and bottom textures
		glBindTexture(GL_TEXTURE_2D, treadTex[0]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data); 
	}

	if (TextureImage[0])
	{
		if (TextureImage[0]->data)
		{
			free(TextureImage[0]->data);
		}

		free(TextureImage[0]);
	}

	if (TextureImage[0]=LoadBMP("data/largeTread.bmp"))
	{
		Status = true;
		glGenTextures(1, &treadTex[1]);
		// Create front and back textures
		glBindTexture(GL_TEXTURE_2D, treadTex[1]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data); 
	}

	if (TextureImage[0])
	{
		if (TextureImage[0]->data)
		{
			free(TextureImage[0]->data);
		}

		free(TextureImage[0]);
	}

	if(TextureImage[0]=LoadBMP("data/sideTread.bmp"))
	{
		Status = true;
		glGenTextures(1, &treadTex[2]);
		// Create left and right textures
		glBindTexture(GL_TEXTURE_2D, treadTex[2]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST); 
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data); 
	}

	if (TextureImage[0])
	{
		if (TextureImage[0]->data)
		{
			free(TextureImage[0]->data);
		}

		free(TextureImage[0]);
	}

	if (TextureImage[0]=LoadBMP("data/bodyFace.bmp"))
	{
		Status = true;
		glGenTextures(1, &treadTex[3]);
		// Create front and back textures
		glBindTexture(GL_TEXTURE_2D, treadTex[3]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data); 
	}

	if (TextureImage[0])
	{
		if (TextureImage[0]->data)
		{
			free(TextureImage[0]->data);
		}

		free(TextureImage[0]);
	}

	if (TextureImage[0]=LoadBMP("data/charSide.bmp"))
	{
		Status = true;
		glGenTextures(1, &treadTex[4]);
		// Create front and back textures
		glBindTexture(GL_TEXTURE_2D, treadTex[4]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data); 
	}

	if (TextureImage[0])
	{
		if (TextureImage[0]->data)
		{
			free(TextureImage[0]->data);
		}

		free(TextureImage[0]);
	}

	if (TextureImage[0]=LoadBMP("data/turretSide.bmp"))
	{
		Status = true;
		glGenTextures(1, &treadTex[5]);
		// Create front and back textures
		glBindTexture(GL_TEXTURE_2D, treadTex[5]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data); 
	}

	if (TextureImage[0])
	{
		if (TextureImage[0]->data)
		{
			free(TextureImage[0]->data);
		}

		free(TextureImage[0]);
	}

	if (TextureImage[0]=LoadBMP("data/turretTop.bmp"))
	{
		Status = true;
		glGenTextures(1, &treadTex[6]);
		// Create front and back textures
		glBindTexture(GL_TEXTURE_2D, treadTex[6]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data); 
	}

	if (TextureImage[0])
	{
		if (TextureImage[0]->data)
		{
			free(TextureImage[0]->data);
		}

		free(TextureImage[0]);
	}

	if (TextureImage[0]=LoadBMP("data/barrel.bmp"))
	{
		Status = true;
		glGenTextures(1, &treadTex[7]);
		// Create front and back textures
		glBindTexture(GL_TEXTURE_2D, treadTex[7]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data); 
	}

	if (TextureImage[0])
	{
		if (TextureImage[0]->data)
		{
			free(TextureImage[0]->data);
		}

		free(TextureImage[0]);
	}

	if (TextureImage[0]=LoadBMP("data/battelTip.bmp"))
	{
		Status = true;
		glGenTextures(1, &treadTex[8]);
		// Create front and back textures
		glBindTexture(GL_TEXTURE_2D, treadTex[8]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data); 
	}

	if (TextureImage[0])
	{
		if (TextureImage[0]->data)
		{
			free(TextureImage[0]->data);
		}

		free(TextureImage[0]);
	}

	if (TextureImage[0]=LoadBMP("data/treadTop.bmp"))
	{
		Status = true;
		glGenTextures(1, &treadTex[9]);
		// Create front and back textures
		glBindTexture(GL_TEXTURE_2D, treadTex[9]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data); 
	}

	if (TextureImage[0])
	{
		if (TextureImage[0]->data)
		{
			free(TextureImage[0]->data);
		}

		free(TextureImage[0]);
	}

	if (TextureImage[0]=LoadBMP("data/tankWheels.bmp"))
	{
		Status = true;
		glGenTextures(1, &treadTex[10]);
		// Create front and back textures
		glBindTexture(GL_TEXTURE_2D, treadTex[10]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data); 
	}

	if (TextureImage[0])
	{
		if (TextureImage[0]->data)
		{
			free(TextureImage[0]->data);
		}

		free(TextureImage[0]);
	}

	if (TextureImage[0]=LoadBMP("data/grass.bmp"))
	{
		Status = true;
		glGenTextures(1, &terrainTex[0]);
		// Create front and back textures
		glBindTexture(GL_TEXTURE_2D, terrainTex[0]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data); 
	}

	if (TextureImage[0])
	{
		if (TextureImage[0]->data)
		{
			free(TextureImage[0]->data);
		}

		free(TextureImage[0]);
	}

	if (TextureImage[0]=LoadBMP("data/bullet.bmp"))
	{
		Status = true;
		glGenTextures(1, &weaponTex[0]);
		// Create front and back textures
		glBindTexture(GL_TEXTURE_2D, weaponTex[0]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data); 
	}

	if (TextureImage[0])
	{
		if (TextureImage[0]->data)
		{
			free(TextureImage[0]->data);
		}

		free(TextureImage[0]);
	}

	return Status; //end of function bracet way down below

}

//-------------------------------------------------------------
//	Function Declarations
//-------------------------------------------------------------
LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


//-------------------------------------------------------------
// Resizing the screen
//-------------------------------------------------------------
GLvoid ReSizeGLScene(GLsizei width, GLsizei height)
{
	if (height==0)
	{
		height=1;
	}
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//--------------------------------------------
// Initialize OpenGl
//--------------------------------------------
int InitGL(GLvoid)
{

	if (!LoadGLTextures())
	{
		return false;
	}

	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);		// Smoooooooooooooooooooth shading bieatch
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Depth buffer stuff----
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Best perspective

	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);

	return true;
}


//-----------------------------------------------
// Drawing the scene
//-----------------------------------------------
int DrawGLScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();														///////////////////
	gluLookAt(40.0f, 30.0f, 40.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);		// Set up the scene
	glPushMatrix();															///////////////////

	test.draw();		// draw tank1

	glPopMatrix();
	glPushMatrix();


	test2.draw();		// draw tank2

	glPopMatrix();
	glPushMatrix();
	
	eatMe.draw();		// draw the field of play

	for(Weapon *cursor = shotCursor; cursor != NULL; cursor = cursor = cursor->next)
	// draw any shots fired by tank1
	{	
		glPopMatrix();
		glPushMatrix();
		cursor->draw();
	}

	for(cursor = shot2Cursor; cursor != NULL; cursor = cursor = cursor->next)
	// draw any shots fired by tank2
	{
		glPopMatrix();
		glPushMatrix();
		cursor->draw();
	}

	return true;
}

//-----------------------------------------------
// Shoving a pound of C-4 up the windows ass
//-----------------------------------------------
GLvoid KillGLWindow(GLvoid)
{
	if (fullscreen)
	{
		ChangeDisplaySettings(NULL, 0);
		ShowCursor(true);
	}

	if (hRC)		// check to see if we have a rendering context
	{
		if (!wglMakeCurrent(NULL,NULL))	// release R context
		{
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		if (!wglDeleteContext(hRC))	// delete R context
		{
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		hRC = NULL;
	}

	if (hDC && !ReleaseDC(hWnd,hDC))		// check to see if we have a device context
	{
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hDC = NULL;
	}

	if (hWnd && !DestroyWindow(hWnd))		// check to see if we have a handle
	{
		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;
	}

	if (!UnregisterClass("OpenGL",hInstance))	// Unregister the windows class
	{
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;
	}
}


//-------------------------------------
// Create the damn window
//-------------------------------------
// This will give us the options of either creating a fullscreen window or a
//	window-ed window  <--GAY
BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{

	GLuint PixelFormat;		// pixel format for us, woopee

	WNDCLASS crappyWindowsFreikinClass_Godamnit;

	DWORD dwExStyle;		// Windows extended style
	DWORD dwStyle;			// Window style

	// Get window in a RECT
	RECT WindowRect;
	WindowRect.left=(long)0;
	WindowRect.right=(long)width;
	WindowRect.top=(long)0;
	WindowRect.bottom=(long)height;

	fullscreen = fullscreenflag;		// set our fullscreen or not thingy

	// Set up our window with stuff we want
	hInstance											= GetModuleHandle(NULL);
	crappyWindowsFreikinClass_Godamnit.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	crappyWindowsFreikinClass_Godamnit.lpfnWndProc		= (WNDPROC) WndProc;
	crappyWindowsFreikinClass_Godamnit.cbClsExtra		= 0;
	crappyWindowsFreikinClass_Godamnit.cbWndExtra		= 0;
	crappyWindowsFreikinClass_Godamnit.hInstance		= hInstance;
	crappyWindowsFreikinClass_Godamnit.hIcon			= LoadIcon(NULL, IDI_WINLOGO);
	crappyWindowsFreikinClass_Godamnit.hCursor			= LoadCursor(NULL, IDC_ARROW);
	crappyWindowsFreikinClass_Godamnit.hbrBackground	= NULL;
	crappyWindowsFreikinClass_Godamnit.lpszMenuName		= NULL;
	crappyWindowsFreikinClass_Godamnit.lpszClassName	= "OpenGL";

	// register the windows class
	if (!RegisterClass(&crappyWindowsFreikinClass_Godamnit))
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;
	}

	// Decide how we want to make the window and make it, fullscreen or 
	//	however we want to make it
	if (fullscreen)
	{
		DEVMODE dmScreenSettings;

		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));

		dmScreenSettings.dmSize=sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth	= width;
		dmScreenSettings.dmPelsHeight	= height;
		dmScreenSettings.dmBitsPerPel	= bits;
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		// Try and make it fullscreen
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			MessageBox(NULL,"Failed to create FullScreen Mode.", "ERROR", MB_OK|MB_ICONEXCLAMATION);
			return false;
		}
	}

	if (fullscreen)
	{
		dwExStyle = WS_EX_APPWINDOW;
		dwStyle = WS_POPUP;
		ShowCursor(false);
	}
	else	// not fullscreen
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		dwStyle=WS_OVERLAPPEDWINDOW;
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);	// adjust window to true requested size


	// Create the damn window already!!!
	if (!(hWnd=CreateWindowEx(	dwExStyle,				// Extended Style For The Window
					"OpenGL",							// Class Name
					title,								// Window Title
					WS_CLIPSIBLINGS |					// Required Window Style
					WS_CLIPCHILDREN |					// Required Window Style
					dwStyle,							// Selected Window Style
					0, 0,								// Window Position
					WindowRect.right-WindowRect.left,	// Calculate Adjusted Window Width
					WindowRect.bottom-WindowRect.top,	// Calculate Adjusted Window Height
					NULL,								// No Parent Window
					NULL,								// No Menu
					hInstance,							// Instance
					NULL)))								// Don't Pass Anything To WM_CREATE
	{
		// GET THE HELL OUTA DODGE!!
		KillGLWindow();
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;
	}

	static	PIXELFORMATDESCRIPTOR pfd=					// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),					// Size Of This Pixel Format Descriptor
		1,												// Version Number
		PFD_DRAW_TO_WINDOW |							// Format Must Support Window
		PFD_SUPPORT_OPENGL |							// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,								// Must Support Double Buffering
		PFD_TYPE_RGBA,									// Request An RGBA Format
		bits,											// Select Our Color Depth
		0, 0, 0, 0, 0, 0,								// Color Bits Ignored
		0,												// No Alpha Buffer
		0,												// Shift Bit Ignored
		0,												// No Accumulation Buffer
		0, 0, 0, 0,										// Accumulation Bits Ignored
		16,												// 16Bit Z-Buffer (Depth Buffer)
		0,												// No Stencil Buffer
		0,												// No Auxiliary Buffer
		PFD_MAIN_PLANE,									// Main Drawing Layer
		0,												// Reserved
		0, 0, 0											// Layer Masks Ignored
	};

	// Get an openGL device context
	if (!(hDC=GetDC(hWnd)))
	{
		KillGLWindow();
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;
	}

	// Get a pixel format
	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))
	{
		KillGLWindow();
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;
	}

	// Set the pixel format
	if(!SetPixelFormat(hDC,PixelFormat,&pfd))
	{
		KillGLWindow();
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;
	}

	// Get Rendering context
	if (!(hRC=wglCreateContext(hDC)))
	{
		KillGLWindow();
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;
	}

	// Make Rendering Context Active...FINALLY!!!
	if(!wglMakeCurrent(hDC,hRC))
	{
		KillGLWindow();
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;
	}

	ShowWindow(hWnd,SW_SHOW);				// Show The Window
	SetForegroundWindow(hWnd);				// Slightly Higher Priority
	SetFocus(hWnd);							// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);			// Set up perspective

	// Initialize our window
	if (!InitGL())
	{
		KillGLWindow();
		MessageBox(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;
	}

	return true;
}


//-------------------------------------
// Handle the window's messages
//-------------------------------------
LRESULT CALLBACK WndProc(	HWND	hWnd,		// Handle For This Window
				UINT	uMsg,					// Message For This Window
				WPARAM	wParam,					// Additional Message Information
				LPARAM	lParam)					// Additional Message Information
{
	switch (uMsg)
	{
		case WM_ACTIVATE:
		{
			if (!HIWORD(wParam))
			{
				active=TRUE;
			}
			else
			{
				active=FALSE;
			}

			return 0;
		}
		case WM_SYSCOMMAND:
		{
			switch (wParam)
			{
				case SC_SCREENSAVE:
				case SC_MONITORPOWER:
				return 0;
			}
			break;
		}
		case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}
		case WM_KEYDOWN:
		{
			keys[wParam] = TRUE;
			return 0;
		}
		case WM_KEYUP:
		{
			keys[wParam] = FALSE;
			return 0;
		}
				case WM_SIZE:
		{
			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));
			return 0;
		}
	}

	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}


//-----------------------------------------------------
// MAIN GAME LOOP
//-----------------------------------------------------
void GameLoop()
{
	tank1 = &test;
	tank2 = &test2;

	if (keys[VK_UP] && ifNCollide(tank1, tank2) && test.DorA())	// move tank1 forward
	{
		test.move(FORWARD);
	}

	if (keys['W'] && ifNCollide(tank1, tank2) && test2.DorA())		// move tank2 forward
	{
		test2.move(FORWARD);
	}

	if (keys[VK_DOWN] && test.DorA())	// move tank1 back
	{
		test.move(BACK);
	}

	if (keys['S'] && test2.DorA())		// move tank1 back
	{
		test2.move(BACK);
	}

	if (keys[VK_RIGHT] && test.DorA())	// turn tank1 to the left
	{
		test.turn(RIGHT);
	}

	if (keys['D'] && test2.DorA())		// turn tank2 to the left
	{
		test2.turn(RIGHT);
	}

	if (keys[VK_LEFT] && test.DorA())	// turn tank1 to the right
	{
		test.turn(LEFT);
	}

	if (keys['A'] && test2.DorA())	// turn tank2 to the right
	{
		test2.turn(LEFT);
	}

	if (keys[VK_CONTROL] && test.DorA()) // tank1 fire weapon
	{
		if (shotCursor == NULL )	// no shots fired
		{
			tank1Shot = new Bullet;
			tank1Shot->initialize(test.getX(), test.getZ(), test.getAngle());
			tank1Shot->weaponTex = weaponTex;
			tank1Shot->next = NULL;

			shotCursor = tank1Shot;
			lastShot = tank1Shot;
		}
		else	// at least 1 shot has been fired
		{
			tank1Shot = new Bullet;
			tank1Shot->next = NULL;
			tank1Shot->initialize(test.getX(), test.getZ(), test.getAngle());
			tank1Shot->weaponTex = weaponTex;

			lastShot->next = tank1Shot;
			lastShot = tank1Shot;
		}
		
	}

	if (keys[VK_TAB] && test2.DorA()) // tank2 fire weapon
	{
		if (shot2Cursor == NULL )	// no shots fired
		{
			tank2Shot = new Bullet;
			tank2Shot->initialize(test2.getX(), test2.getZ(), test2.getAngle());
			tank2Shot->weaponTex = weaponTex;
			tank2Shot->next = NULL;

			shot2Cursor = tank2Shot;
			lastShot2 = tank2Shot;
		}
		else	// at least 1 shot has been fired
		{
			tank2Shot = new Bullet;
			tank2Shot->next = NULL;
			tank2Shot->initialize(test2.getX(), test2.getZ(), test2.getAngle());
			tank2Shot->weaponTex = weaponTex;


			lastShot2->next = tank2Shot;
			lastShot2 = tank2Shot;
		}
		
	}


	if ( shotCursor != NULL ) // move bullets
	{
		Weapon *cursor;
		Weapon *foo = NULL;
		Weapon *newList = NULL;
		Weapon *newListCursor = NULL;

		for ( cursor = shotCursor; cursor != NULL; cursor = cursor->next)
		{
			if( foo != NULL )	// release memory of foo
			{
				delete foo;		
				foo = NULL;
			}
			
			if(!ifNCollide(tank2, cursor))
			{
				// bullet hit the tank, remove it
				foo = cursor;
			}
			else
			{
				cursor->move(FORWARD);

				if(newList == NULL)	// nothing in new list, put the first thing in
				{
					newList = cursor;
					newListCursor = newList;
				}
				else	// newList has at least 1 thing in it, put another on the end
				{
					newListCursor->next = cursor;
					newListCursor = newListCursor->next;
				}
			}
		}

		if(foo != NULL)
			delete foo;

		if(newListCursor != NULL)
			newListCursor->next = NULL;

		shotCursor = newList;
		lastShot = newListCursor;
	}

	if ( shot2Cursor != NULL ) // move bullets
	{
		Weapon *cursor;
		Weapon *foo = NULL;
		Weapon *newList = NULL;
		Weapon *newListCursor = NULL;

		for ( cursor = shot2Cursor; cursor != NULL; cursor = cursor->next)
		{
			if( foo != NULL )	// release memory of foo
			{
				delete foo;		
				foo = NULL;
			}
			
			if(!ifNCollide(tank1, cursor))
			{
				// bullet hit the tank, remove it
				foo = cursor;
			}
			else
			{
				cursor->move(FORWARD);

				if(newList == NULL)	// nothing in new list, put the first thing in
				{
					newList = cursor;
					newListCursor = newList;
				}
				else	// newList has at least 1 thing in it, put another on the end
				{
					newListCursor->next = cursor;
					newListCursor = newListCursor->next;
				}
			}
		}

		if(foo != NULL)
			delete foo;

		if(newListCursor != NULL)
			newListCursor->next = NULL;

		shot2Cursor = newList;
		lastShot2 = newListCursor;
	}


	DrawGLScene();		// Draw our stuff
	SwapBuffers(hDC);	// Swap the buffers for double buffering

	if (keys[VK_CONTROL])
	{
		keys[VK_CONTROL] = false;
	}

	if (keys[VK_TAB])
	{
		keys[VK_TAB] = false;
	}

	return;
}


//-----------------------------------------------------
// Start the freikin program already
//-----------------------------------------------------
int WINAPI WinMain(	HINSTANCE	hInstance,
					HINSTANCE	hPrevInstance,
					LPSTR		lpCmdLine,
					int		nCmdShow)
{
	MSG messages;			// Mesages
	bool done = false;		// Is our game done or not?

	test.treadTex = treadTex; //setting the texure array pointers equal
	eatMe.terrainTex = terrainTex; // this allows us to uses them in our classes
	test2.treadTex = treadTex;

	shotCursor = NULL;

	// Create our OpenGL window!!!!!
	if (!CreateGLWindow("Jason & Andy's OpenGL",1024,768,32,fullscreen))
	{
		return 0;
	}

	while(!done)
	{
		if (PeekMessage(&messages,NULL,0,0,PM_REMOVE))	// take care of messages
		{
			if (messages.message==WM_QUIT)	// Stop running
			{
				done=TRUE;	// set done to true so we can quit
			}
			else
			{
				TranslateMessage(&messages);				// Translate The Message
				DispatchMessage(&messages);				// Dispatch The Message
			}
		}
		else								// If There Are No Messages
		{
			if (active)
			{
				if (keys[VK_ESCAPE])
				{
					done = true;
				}
				else
				{
					GameLoop();
				}
			}
		}
	}
	

	KillGLWindow();				// destroy our window
	return(messages.wParam);		// Exit the program
}