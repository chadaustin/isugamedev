// SkyDome Demo  -  October 2001
//
// Luis R. Sempé
// visual@spheregames.com
// Sphere Games (http://www.spheregames.com)
// 
// You may use, copy, distribute or create derivative software
// for any purpose. If you do, I'd appreciate it if you write me 
// and let me know what you do with it. Thanks!
// Have fun!
////////////////////////////////////////////////////

#ifndef SKYDOME_H_
#define SKYDOME_H_

#include "globals.h"

void GenerateDome(float radius, float dtheta, float dphi, float hTile, float vTile);
int RenderSkyDome();
void ReleaseDome();

#endif