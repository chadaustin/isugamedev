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

	virtual GLfloat getX() { return 0.0;};
	virtual GLfloat getY() { return 0.0;};
	virtual GLfloat getZ() { return 0.0;};
	virtual GLfloat getExtents() { return 0.0;};

};

#endif // !defined(AFX_GENERIC_H__E2AE6F50_B697_11D5_9A49_0001023C9BC6__INCLUDED_)
