// Bullet.h: interface for the Bullet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BULLET_H__5A7CA2E2_AD18_11D5_98FF_0001023C9B87__INCLUDED_)
#define AFX_BULLET_H__5A7CA2E2_AD18_11D5_98FF_0001023C9B87__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Weapon.h"

class Bullet : public Weapon  
{
public:
	Bullet();
	virtual ~Bullet();

	void draw();

};

#endif // !defined(AFX_BULLET_H__5A7CA2E2_AD18_11D5_98FF_0001023C9B87__INCLUDED_)
