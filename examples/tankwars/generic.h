// generic.h: interface for the generic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GENERIC_H__E2AE6F50_B697_11D5_9A49_0001023C9BC6__INCLUDED_)
#define AFX_GENERIC_H__E2AE6F50_B697_11D5_9A49_0001023C9BC6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>

class generic  
{
public:
	generic();
	virtual ~generic();

	virtual GLfloat getX() { return xPos;};
	virtual GLfloat getY() { return yPos;};
	virtual GLfloat getZ() { return zPos;};
	virtual GLfloat getExtents() { return extents;};

protected:

	GLfloat xPos;
	GLfloat yPos;
	GLfloat zPos;
	GLfloat speed;
	GLfloat angle;
	GLfloat extents;

};

#endif // !defined(AFX_GENERIC_H__E2AE6F50_B697_11D5_9A49_0001023C9BC6__INCLUDED_)
