#ifndef SKYDOME_H_
#define SKYDOME_H_

void GenerateDome(float radius, float dtheta, float dphi, float hTile, float vTile);
//GenerateDome(200.0f, 5.0f, 5.0f, 1.0f, 1.0f);
int RenderSkyDome();
void ReleaseDome();

#endif