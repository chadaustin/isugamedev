// Aster
// asteroids... first person shooter style.
//
// kevin meinert - kevin@vrsource.org
// Public domain
//
// Ported to VRJuggler by Chad Austin - aegisk@vrac.iastate.edu

#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <math.h>

#include <vrj/Kernel/Kernel.h>
#include <vrj/Draw/OGL/GlApp.h>
#include <gadget/Type/PositionInterface.h>
#include <gadget/Type/DigitalInterface.h>
#include <gmtl/Generate.h>
//#include <gmtl/Vec.h>
//#include <gmtl/VecOps.h>
//#include <gmtl/Xforms.h>

#include "cubeGeometry.h"
#include "Utility.h"


using namespace gmtl;
using gmtl::Math::unitRandom;
using gmtl::Math::rangeRandom;


inline float distance(const Vec3f& v1, const Vec3f& v2)
{
    return length(v1 - v2);
}

// compute perfectly elastic reflection using available vectors...
inline Vec3f reflect(
    const Vec3f& incoming,
    const Vec3f& surfacenormal)
{
    float d = dot(-incoming, surfacenormal);
    return surfacenormal * d * 2.0f + incoming;
}

template<typename T>
void negate(T& t) {
    t = -t;
}

class Entity {
public:
    Entity() {
        _size = 1.0f;
        _timeToLive = -1;
    }

    void draw() {
        glPushMatrix();
        glTranslate(_position);
        float scale = _size * 0.5f;
        glScalef(scale, scale, scale);
        _cube.render();
        glPopMatrix();
    }

    void update(float dt) {
        _position += _velocity * dt;
        if (_timeToLive != -1)
            _timeToLive -= dt;
    }

    void setSize(float size) {
        _size = size;
    }

    void setTimeToLive(float timeToLive) {
        _timeToLive = timeToLive;
    }

    bool isAlive() {
        return (_timeToLive == -1 || _timeToLive > 0);
    }

    float getSize() {
        return _size;
    }

    void setPos(const Vec3f& pos) {
        _position = pos;
    }
    void setPos( float x, float y, float z ) {
        _position[0] = x;
        _position[1] = y;
        _position[2] = z;
    }

    Vec3f& getPos() {
        return _position;
    }

    void setVel(const Vec3f& vel) {
        _velocity = vel;
    }
    void setVel(float x, float y, float z) {
        setVel(Vec3f(x, y, z));
    }

    Vec3f& getVel() {
        return _velocity;
    }

private:
    float _size;
    float _timeToLive; // -1 is infinite == don't ever die;
    Vec3f _velocity;
    Vec3f _position;
    cubeGeometry _cube;
};

class Projectile : public Entity {};
class Roid       : public Entity {};
class Ship       : public Entity {};


const int BOARD_SIZE = 15;


void drawGrid() {
    glColor3f(0.3f, 0.2f,0.6f);
    glPushMatrix();
    glBegin(GL_LINES);
    for (float x = -BOARD_SIZE; x <= BOARD_SIZE; ++x) {
        glVertex3f(-BOARD_SIZE, 0, x);
        glVertex3f( BOARD_SIZE, 0, x);
        glVertex3f(x, 0, -BOARD_SIZE);
        glVertex3f(x, 0,  BOARD_SIZE);
    }
    glEnd();
    glPopMatrix();
}


// game setup (configuration options)
const float SCALE          = 5.0f;
const float projVelocity   = 20.0f;
const float projSize       = 0.1f;
const float projTimeToLive = 2.0f;
const float shipAccel      = 0.5f;
const float roidSize       = 3.0f;
const float roidMaxSpeed   = 3.0f;


class JuggleroidsApp : public vrj::GlApp {
public:
    JuggleroidsApp() {
        for (int x = -5; x <= 5; x += 10) {
            for (int z = -5; z <= 5; z += 10) {
                Roid r;
                r.setSize(roidSize);
                r.setPos(x, 0, z);
                float dx = unitRandom() * roidMaxSpeed;
                float dz = unitRandom() * roidMaxSpeed;
                r.setVel(dx, 0, dz);
                roids.push_back(r);
            }
        }
    }


    void init() {
        _head.init("VJHead");
        _wand.init("VJWand");
        _buttonFire.init("VJButton0");
        _buttonAccel.init("VJButton3");
        _buttonDecel.init("VJButton5");

        _lastUpdate = vpr::Interval::now();
    }


    void contextInit() {
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }


    void bufferPreDraw() {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }


    void draw() {
        glClear(GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glPushMatrix();
        glScalef(SCALE, SCALE, SCALE);
        glTranslate(-ship.getPos());

        for (unsigned x = 0; x < roids.size(); ++x) {
            roids[x].draw();
        }
        for (unsigned x = 0; x < projs.size(); ++x) {
            projs[x].draw();
        }
        drawGrid();
        glPopMatrix();
    }


    void preFrame() {
        vpr::Interval now = vpr::Interval::now();
        const float dt = (now - _lastUpdate).secf();
        _lastUpdate = now;

        update(dt);
    }

    void update(float dt) {
        ship.update(dt);
        for (unsigned x = 0; x < roids.size(); ++x) {
            roids[x].update(dt);
        }
        for (unsigned x = 0; x < projs.size(); ++x) {
            projs[x].update(dt);
        }

        // Get wand location and orientation in game world coordinates.
        Matrix44f m = *(_wand->getData());;
        Vec3f wandTranslation = makeTrans<Vec3f>(m) / SCALE + ship.getPos();
        Vec3f wandOrientation;
        xform(wandOrientation, m, Vec3f(0, 0, -1));
        normalize(wandOrientation);

        if (_buttonFire->getData() == gadget::Digital::TOGGLE_ON) {
            // fire in the direction the wand faces
            Projectile proj;
            proj.setPos(wandTranslation);
            proj.setVel(wandOrientation * projVelocity);
            proj.setSize(projSize);
            proj.setTimeToLive(projTimeToLive);
            projs.push_back(proj);
        }

        Vec3f shipAcceleration = wandOrientation;
        shipAcceleration[1] = 0;  // zero out the y component
        normalize(shipAcceleration);

        // acceleration
        if (_buttonAccel->getData() == gadget::Digital::TOGGLE_ON ||
            _buttonAccel->getData() == gadget::Digital::ON)
        {
            ship.setVel(ship.getVel() + shipAcceleration * shipAccel);
        }

        // deceleration
        if (_buttonDecel->getData() == gadget::Digital::TOGGLE_ON ||
            _buttonDecel->getData() == gadget::Digital::ON)
        {
            ship.setVel(ship.getVel() - shipAcceleration * shipAccel);
        }


        //////////////
        // GAME LOGIC
        // collisions, roid bounce, removing, etc..
        //////////////


        // do asteroid bounce with the walls of the arena.
        //const float eps = 0.01f;
        for (unsigned i = 0; i < roids.size(); ++i) {
            Roid& r = roids[i];
            for (unsigned j = 0; j < 3; ++j) {
                if (r.getPos()[j] > BOARD_SIZE || r.getPos()[j] < -BOARD_SIZE) {
                    negate(r.getVel()[j]);
                }
            }
        }

        // do bounce on the ship with the edges of the arena.
        float dampen = 0.8f;
        float shipX = ship.getPos()[0];
        float shipZ = ship.getPos()[2];
        if (shipX > BOARD_SIZE || shipX < -BOARD_SIZE)
            ship.getVel()[0] *= -dampen;
        if (shipZ > BOARD_SIZE || shipZ < -BOARD_SIZE)
            ship.getVel()[2] *= -dampen;

        // remove projectiles that are too old
        std::vector<Projectile> keep;
        for (unsigned i = 0; i < projs.size(); ++i) {
            if (projs[i].isAlive()) {
                keep.push_back(projs[i]);
            }
        }
        projs = keep;

/*
        // do collision between ship and asteroids...
        for (unsigned i = 0; i < roids.size(); ++i)
        {
            Roid& r = roids[i];
            // get dist from ship to center of roid (treat roid as sphere for simplicity)
            float dist = Math::distance( ship.getPos(), r.getPos() );
            float min_dist_between_ship_and_roid = (r.getSize() + ship.getSize());

            // if too close, then collision...
            if (dist < min_dist_between_ship_and_roid)
            {
                // get vector from roid to ship (normal to collision angles)
                Vec3f normal = ship.getPos() - r.getPos();
                Math::norm( normal );

                // reflect velocity only if moving toward each other
                if (Math::dot( ship.getVel(), normal ) < 0)
                {
                    // compute perfectly elastic reflection
                    Vec3f reflectionVector;
                    Math::reflect( reflectionVector, ship.getVel(), normal );

                    // dampen resulting reflection
                    ship.setVel(reflectionVector * dampen);
                }

                // asteroids can push the ship around... (affects position)
                Vec3f vec, newposition;
                vec = ship.getPos() - r.getPos();
                Math::norm( vec );
                vec *= min_dist_between_ship_and_roid;
                newposition = r.getPos() + vec;

                // set the new ship position and velocity
                Vec3f additional_velocity_from_impact;
                additional_velocity_from_impact = newposition - ship.getPos();
                ship.setVel(ship.getVel() + additional_velocity_from_impact);
                ship.setPos( newposition );
            }
        }
*/

        // do collision between projectile and asteroids...
        for (std::vector<Roid>::iterator itr = roids.begin(); itr != roids.end(); ++itr)
        {
            for (std::vector<Projectile>::iterator pitr = projs.begin(); pitr != projs.end(); ++pitr)
            {
                // get dist from bullet to center of roid (treat roid as sphere for simplicity)
                float dist = distance(pitr->getPos(), itr->getPos());

                // consider the size of the roid (smaller is harder to hit because the distance will need to be much closer)
                // the dist between object centers should be less than the sum of the two radii
                if (dist < (itr->getSize() + pitr->getSize()))
                {
                    Roid aster = (*itr);

                    // remove the hit asteroid, and the hit projectile
                    roids.erase( itr );
                    projs.erase( pitr );

                    // if it was big enough, replace it with two smaller ones...
                    if (aster.getSize() > 0.5f) // .25 is smallest size roid can break into
                    {
                        Roid r;
                        r.setSize(aster.getSize() / 2.0f);
                        r.setPos( aster.getPos()[0], aster.getPos()[1], aster.getPos()[2] );
                        r.setVel( unitRandom() * roidMaxSpeed, 0, unitRandom() * roidMaxSpeed );
                        roids.push_back( r );

                        r.setPos( aster.getPos()[0], aster.getPos()[1], aster.getPos()[2] );
                        r.setVel( unitRandom() * roidMaxSpeed, 0, unitRandom() * roidMaxSpeed );
                        roids.push_back( r );
                    }

                    return; // WARNING: don't put any code after this for loop!
                }
            }
        }
    }

    gadget::PositionInterface _head;
    gadget::PositionInterface _wand;
    gadget::DigitalInterface  _buttonFire;
    gadget::DigitalInterface  _buttonAccel;
    gadget::DigitalInterface  _buttonDecel;

    vpr::Interval _lastUpdate;

    Ship ship;
    std::vector<Projectile> projs;
    std::vector<Roid> roids;
};


int main(int argc, const char* argv[]) {
    vrj::Kernel* kernel = vrj::Kernel::instance();
    for (int i = 1; i < argc; ++i) {
        kernel->loadConfigFile(argv[i]);
    }

    kernel->start();
    std::auto_ptr<vrj::App> app(new JuggleroidsApp());
    kernel->setApplication(app.get());
    kernel->waitForKernelStop();
}
