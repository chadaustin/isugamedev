#include <GL/glut.h>
#include <stdlib.h>
#include "SnowSystem.h"


inline float frand() {
  return float(rand()) / RAND_MAX;
}


const int BASE_HEIGHT = 10;


SnowSystem::SnowSystem() {
  Particle* p = mParticles;
  for (int i = 0; i < SNOWFLAKE_COUNT; ++i) {
    p->x = frand() - 0.5f;
    p->y = frand() - 0.5f;
    p->z = frand() * BASE_HEIGHT;
    p->velocity = frand() * 2 + 2;
    ++p;
  }
}


SnowSystem::~SnowSystem() {
}


void
SnowSystem::draw() {
  glBegin(GL_POINTS);
  glDepthMask(GL_FALSE);

  glColor3f(1, 1, 1);
  Particle* p = mParticles;
  for (int i = 0; i < SNOWFLAKE_COUNT; ++i) {
    glVertex3f(p->x, p->y, p->z);
    ++p;
  }

  glDepthMask(GL_TRUE);
  glEnd();
}


void
SnowSystem::update(int elapsedTime) {
  Particle* p = mParticles;
  for (int i = 0; i < SNOWFLAKE_COUNT; ++i) {
    p->z -= elapsedTime * p->velocity * 0.0001f;
    if (p->z < 0) {
      p->z = BASE_HEIGHT;
    }

    ++p;
  }
}
