#include <list>
#include "Vec3.h"
#include "Particle.h"
#include "ParticleSystem.h"
#include "Force.h"

//: apply this force function to the particle
void GlobalForce::operator()( ParticleSystem& ps )
{
   std::vector<Particle*>::iterator it;
   for ( it = ps.particles().begin(); it != ps.particles().end(); ++it)
   {
      Particle& p = *(*it);
      if (this->isIgnored(&p) == false)
      {
         p.applyForce( mForce );
      }
   }
}

//: apply this force function to the particle
void ViscousDrag::operator()( ParticleSystem& ps )
{
   std::vector<Particle*>::iterator it;
   for ( it = ps.particles().begin(); it != ps.particles().end(); ++it)
	{
		Particle& p = *(*it);
      if (this->isIgnored( &p ) == false)
      {
		   // Calculate the force nesesary to knock of kV velocity

		   // get the velocity we need to reduce particles speed
		   // eqn: V(new) = V - kV, where k is a coeficient between 0..1
		   Vec3<float> antiVelocity = p.velocity() * (-_dragCoef);

		   // how much do we have to decelerate it to achieve 'newDesiredVelocity'
		   // decelerateAmount = antiVelocity / timeChange;
		   // NOTE: timeChange is 1.0, so deceleration is just antiVelocity
		   Vec3<float> force = antiVelocity * p.mass();
		   p.applyForce( force );
      }
	}
}

//: apply this force function to the particle
void Acceleration::operator()( ParticleSystem& ps )
{
   std::vector<Particle*>::iterator it;
   for ( it = ps.particles().begin(); it != ps.particles().end(); ++it)
	{
		Particle& p = *(*it);
      if (this->isIgnored( &p ) == false)
		{
         //                     meters
		   // Force = kilograms * ------ = kilograms * acceleration
		   //                     sec^2

		   // calculate how much force it will take to accelerate the particle
		   Vec3<float> force = mAcceleration * p.mass();
		   p.applyForce( force );
         //cout<<"Applied force "<<force[0]<<" "<<force[1]<<" "<<force[2]<<"\n"<<flush;
	   }
   }
}

//: apply this force function to the particle
void Current::operator()( ParticleSystem& ps )
{
   std::vector<Particle*>::iterator it;
   for ( it = ps.particles().begin(); it != ps.particles().end(); ++it)
	{
		Particle& p = *(*it);
      if (this->isIgnored( &p ) == false)
      {
		   //                meters   velocity 
         // acceleration = ------ = --------
         //                sec^2      sec
         Vec3<float>& acc = mSpeed;

         //                     meters
		   // Force = kilograms * ------ = kilograms * acceleration
		   //                     sec^2

		   // calculate how much force it will take to accelerate the particle
		   Vec3<float> force = acc * p.mass();
		   p.applyForce( force );
      }
   }
}

//: apply this force function to the particle
void Spring::operator()( ParticleSystem& ps )
{
   if (mA == NULL || mB == NULL)
      return;

   // does not make sense for this operator to exist if it has nothing 
   // to act upon...
   // note: this could leave the user holding an operator that maybe they thought would stay in the system... oh well, they will have to check the op's isInSystem...
   if (mA->isInSystem() == false || mB->isInSystem() == false)
   {
      ps.remove( this );
      return;
   }

   Particle& a = *mA;
   Particle& b = *mB;

   // ignoring the particle system...
   Vec3<float> spring_offset = a.position() - b.position();
   Vec3<float> speed_of_approach = a.velocity() - b.velocity();

   // calculate the spring force magnitude.
   float spring_force_mag = mSpringConstant * (spring_offset.length() - mRestLength);
   
   // calculate the damping force magnitude.
   float damping_force_mag = mDampeningConstant * ( speed_of_approach.dot( spring_offset ) / spring_offset.length() );
  
   // what direction the force is in
   Vec3<float> direction = (spring_offset / spring_offset.length());
   
   // calculate the force from the spring and damping forces.
   Vec3<float> force = -( direction * (spring_force_mag + damping_force_mag ));

   a.applyForce( force );
   b.applyForce( -force );
}
