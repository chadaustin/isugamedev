// Aster
// asteroids... first person shooter style.
//
// kevin meinert - kevin@vrsource.org
// Public domain
//
// Features:
// - mouselook (no pointer with warp) rotate camera
// - straef
// - air hockey physics
// - alternate keyboard controls (works without mouse)
// - 2 gun turrets on either side...
//
// Usage/Keys:
//
//    -------------------------------------------
//        W                    accel
//      A S D          straef  decel  straef
//    -------------------------------------------
//        up                   accel
//    left  right      rotate         rotate
//       down                  decel
//    -------------------------------------------
//    mouse(x,y) axes          rotate
//    left mouse button        fire
//    -------------------------------------------
//    <SPACEBAR>               fire
//    -------------------------------------------
//
// TODO:
//   - pretty models and textures... (use a model loader)
//   - keep score
//   - keep track of lives (ships)
//   - die when collide with asteroid (no collision performed yet)
//   - add a top-down 2D map or radar screen
//   - let the top down 2D map be one additional way to play the game
//

#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <math.h>

#include <vrj/Kernel/Kernel.h>
#include <vrj/Draw/OGL/GlApp.h>
#include <gadget/Type/PositionInterface.h>
#include <gadget/Type/DigitalInterface.h>
#include <gmtl/Math.h>
#include <gmtl/Vec.h>
#include <gmtl/VecOps.h>

#include "cubeGeometry.h"
#include "Utility.h"


inline float distance(const gmtl::Vec3f& v1, const gmtl::Vec3f& v2)
{
    return gmtl::length(v1 - v2);
}

// compute perfectly elastic reflection using available vectors...
inline void reflect(
    gmtl::Vec3f& reflection,
    const gmtl::Vec3f& incoming,
    const gmtl::Vec3f& surfacenormal)
{
    reflection = incoming * -1.0f;
    float d = gmtl::dot(reflection, surfacenormal);
    reflection = surfacenormal * d * 2.0f + incoming;
}


class BaseObject {
public:
    BaseObject()
        : _size( 1.0f )
        , _timeToLive( -1 )
    {
        setPos( 0.0f, 0.0f, 0.0f );
        setVel( 0.0f, 0.0f, 0.0f );
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

    float getSize() {
        return _size;
    }

    void setPos(const gmtl::Vec3f& pos) {
        _position = pos;
    }
    void setPos( float x, float y, float z ) {
        _position[0] = x;
        _position[1] = y;
        _position[2] = z;
    }

    gmtl::Vec3f& getPos() {
        return _position;
    }

    void setVel(const gmtl::Vec3f& vel) {
        _velocity = vel;
    }
    void setVel(float x, float y, float z) {
        setVel(gmtl::Vec3f(x, y, z));
    }

    gmtl::Vec3f& getVel() {
        return _velocity;
    }

private:
    float _size;
    float _timeToLive; // -1 is infinite == don't ever die;
    gmtl::Vec3f _velocity;
    gmtl::Vec3f _position;
    cubeGeometry _cube;
};

class Projectile : public BaseObject {};
class Roid : public BaseObject {};
class Ship : public BaseObject {};


const float BOARD_SIZE = 15;


void drawGrid() {
    glColor3f( 0.3f, 0.2f, 0.6f );
    glPushMatrix();
    glBegin( GL_LINES );
    for ( float x = -BOARD_SIZE; x < BOARD_SIZE; ++x) {
        glVertex3f( -BOARD_SIZE, 0, x );
        glVertex3f(  BOARD_SIZE, 0, x );
        glVertex3f( x, 0, -BOARD_SIZE );
        glVertex3f( x, 0,  BOARD_SIZE );
    }
    glEnd();
    glPopMatrix();
}


template<typename T>
void negate(T& t) {
    t = -t;
}


// game setup (configuration options)
//const float projVelocity   = 20.0f;
//const float projSize       = 0.1f;
//const float projTimeToLive = 0.75f;
//const float rotVelocity    = 60.0f;
//const float shipAccel      = 10.0f;
const float roidSize       = 3.0f;
const float roidMaxSpeed   = 3.0f;



class JuggleroidsApp : public vrj::GlApp {
public:
    JuggleroidsApp() {
        Roid r;
        r.setSize(roidSize);
        r.setPos( -5.0f, 0.0f, -5.0f );
        r.setVel( gmtl::Math::unitRandom() * roidMaxSpeed, 0, gmtl::Math::unitRandom() * roidMaxSpeed );
        roids.push_back( r );

        r.setPos( -5.0f, 0.0f, 5.0f );
        r.setVel( gmtl::Math::unitRandom() * roidMaxSpeed, 0, gmtl::Math::unitRandom() * roidMaxSpeed );
        roids.push_back( r );

        r.setPos(  5.0f, 0.0f, -5.0f );
        r.setVel( gmtl::Math::unitRandom() * roidMaxSpeed, 0, gmtl::Math::unitRandom() * roidMaxSpeed );
        roids.push_back( r );

        r.setPos(  5.0f, 0.0f, 5.0f );
        r.setVel( gmtl::Math::unitRandom() * roidMaxSpeed, 0, gmtl::Math::unitRandom() * roidMaxSpeed );
        roids.push_back( r );
    }


    void init() {
        _head.init("VJHead");
        _wand.init("VJWand");
        _buttonFire.init("VJButton0");

        _lastUpdate = vpr::Interval::now();
    }


    void contextInit() {
        glEnable( GL_DEPTH_TEST );
        glEnable( GL_BLEND );
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    }


    void bufferPreDraw() {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }


    void draw() {
        glClear(GL_DEPTH_BUFFER_BIT);

        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity();

        glPushMatrix();
        glScalef(5, 5, 5);
        glTranslate( -ship.getPos() );

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
        ship.update( dt );
        for (unsigned x = 0; x < roids.size(); ++x) {
            roids[x].update( dt );
        }
        for (unsigned x = 0; x < projs.size(); ++x) {
            projs[x].update( dt );
        }

        if (_buttonFire->getData() == gadget::Digital::TOGGLE_ON) {
/*
            // fire in the direction the wand faces
            Projectile proj;
            

            // local position on the ship
            float local_pos[3] = { 0, -0.2f, 0.4f };

            // convert the local position to world coord
            float world_offset[3];
            world_offset[0] = shipRight[0] * local_pos[0] + shipUp[0] * local_pos[1] + shipForward[0] * local_pos[2];
            world_offset[1] = shipRight[1] * local_pos[0] + shipUp[1] * local_pos[1] + shipForward[1] * local_pos[2];
            world_offset[2] = shipRight[2] * local_pos[0] + shipUp[2] * local_pos[1] + shipForward[2] * local_pos[2];

            // set the projectile start position (relative to the ships world position)
            proj.setPos( ship.getPos()[0] + world_offset[0],
                         ship.getPos()[1] + world_offset[1],
                         ship.getPos()[2] + world_offset[2] );
            proj.setVel( shipForward[0] * projVelocity,
                         shipForward[1] * projVelocity,
                         shipForward[2] * projVelocity );
            proj.size = projSize;
            proj.timeToLive = projTimeToLive;
            projs.push_back(proj);
*/
        }


        ///////////
        // INPUT:
        ///////////

        // find out what dir, the ship is pointing.
        // - flip the x axis to support right-hand rule
        // - add 90deg so that the identity rotation faces out of the screen
        // - then negate it all because we actually face forward (in 0,0,-1)
/*
        float shipForward[3];
        shipForward[0] = cosf( Math::deg2rad( ship.getRotation() + 90 ) );
        shipForward[1] = 0;
        shipForward[2] = -sinf( Math::deg2rad( ship.getRotation() + 90 ) );

        float shipRight[3];
        shipRight[0] = cosf( Math::deg2rad( ship.getRotation() ) );
        shipRight[1] = 0;
        shipRight[2] = -sinf( Math::deg2rad( ship.getRotation() ) );

        float shipUp[3] = { 0.0f, 1.0f, 0.0f };

        if (fireButton)
        {
            // fire in the direction ship faces
            Projectile proj;

            // local position on the ship
            float local_pos[3] = { 0, -0.2f, 0.4f };

            // convert the local position to world coord
            float world_offset[3];
            world_offset[0] = shipRight[0] * local_pos[0] + shipUp[0] * local_pos[1] + shipForward[0] * local_pos[2];
            world_offset[1] = shipRight[1] * local_pos[0] + shipUp[1] * local_pos[1] + shipForward[1] * local_pos[2];
            world_offset[2] = shipRight[2] * local_pos[0] + shipUp[2] * local_pos[1] + shipForward[2] * local_pos[2];

            // set the projectile start position (relative to the ships world position)
            proj.setPos( ship.getPos()[0] + world_offset[0],
                         ship.getPos()[1] + world_offset[1],
                         ship.getPos()[2] + world_offset[2] );
            proj.setVel( shipForward[0] * projVelocity,
                         shipForward[1] * projVelocity,
                         shipForward[2] * projVelocity );
            proj.size = projSize;
            proj.timeToLive = projTimeToLive;
            projs.push_back( proj );
        }
*/


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

//        const float dampen = 0.8f;// dampen the elastic collision with wall

/*
        // do bounce on the ship with the edges of the arena.
        float outside = 10.0f;// ship can go this much outside the arena before bouncing
        if (ship.getPos()[0] > (BOARD_SIZE+outside) || ship.getPos()[0] < -(BOARD_SIZE+outside))
            ship.getVel()[0] = -ship.getVel()[0] * dampen;
        if (ship.getPos()[1] > (BOARD_SIZE+outside) || ship.getPos()[1] < -(BOARD_SIZE+outside))
            ship.getVel()[1] = -ship.getVel()[1] * dampen;
        if (ship.getPos()[2] > (BOARD_SIZE+outside) || ship.getPos()[2] < -(BOARD_SIZE+outside))
            ship.getVel()[2] = -ship.getVel()[2] * dampen;
*/

/*
        // remove projectiles that are too old
        std::vector<Projectile>::iterator pitr;
        std::vector< std::vector<Projectile>::iterator > proj_remove_queue;
        for (pitr = projs.begin(); pitr != projs.end(); ++pitr)
        {
            if ((*pitr).timeToLive != -1 && (*pitr).timeToLive <= 0)
                proj_remove_queue.push_back( pitr );
        }
        x = proj_remove_queue.size();
        while (x--)
            projs.erase( proj_remove_queue[x] );
*/

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
                gmtl::Vec3f normal = ship.getPos() - r.getPos();
                Math::norm( normal );

                // reflect velocity only if moving toward each other
                if (Math::dot( ship.getVel(), normal ) < 0)
                {
                    // compute perfectly elastic reflection
                    gmtl::Vec3f reflectionVector;
                    Math::reflect( reflectionVector, ship.getVel(), normal );

                    // dampen resulting reflection
                    ship.setVel(reflectionVector * dampen);
                }

                // asteroids can push the ship around... (affects position)
                gmtl::Vec3f vec, newposition;
                vec = ship.getPos() - r.getPos();
                Math::norm( vec );
                vec *= min_dist_between_ship_and_roid;
                newposition = r.getPos() + vec;

                // set the new ship position and velocity
                gmtl::Vec3f additional_velocity_from_impact;
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
                        r.setVel( gmtl::Math::unitRandom() * roidMaxSpeed, 0, gmtl::Math::unitRandom() * roidMaxSpeed );
                        roids.push_back( r );

                        r.setPos( aster.getPos()[0], aster.getPos()[1], aster.getPos()[2] );
                        r.setVel( gmtl::Math::unitRandom() * roidMaxSpeed, 0, gmtl::Math::unitRandom() * roidMaxSpeed );
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
