#ifndef SNOW_SYSTEM_H
#define SNOW_SYSTEM_H


class SnowSystem {
public:
  SnowSystem();
  ~SnowSystem();

  void draw();
  void update(int elapsedTime);

private:
  enum { SNOWFLAKE_COUNT = 1000 };

  struct Particle {
    float x;
    float y;
    float z;
    float velocity;
  };

  Particle mParticles[SNOWFLAKE_COUNT];
};


#endif
