class TriSpring : public ParticleSystem
{
public:
      TriSpring() : ParticleSystem(), a(NULL), b(NULL), c(NULL), velocitizer(0.0f)
      {
         this->init();
      }
      
      virtual void clear()
      {
         ParticleSystem::clear();
         
         if (a != NULL)
         {
            a->deref(); a = NULL;
         }
         if (b != NULL)
         {
            b->deref(); b = NULL;
         }
         if (c != NULL)
         {
            c->deref(); c = NULL;
         }
      }
            
      void init()
      {
         this->clear();

         //ODEsolver* solver = new EulerODEsolver;         // 1st order
         //ODEsolver* solver = new ModifiedEulerODEsolver; // 2nd order
         //ODEsolver* solver = new HeunODEsolver;          // 2nd order
         ODEsolver* solver = new RungeKuttaODEsolver;    // 4th order
         this->setSolver( solver );
         solver->deref();

         // operations
         Gravity* gravity = new Gravity;
         this->add( gravity );
         GrimReaper* reaper = new GrimReaper;
         this->add( reaper );
         ColorWithAge* cwa = new ColorWithAge;
         this->add( cwa );
         ViscousDrag* drag = new ViscousDrag;
         drag->setDrag( 0.39f ); // ??
         this->add( drag );

         setupSpring( *this, gravity );
         
         drag->deref();
         gravity->deref();
         reaper->deref();
         cwa->deref();
      }

      void setupSpring( ParticleSystem& s, GlobalOperator* ignore )
      {
         a = new Particle;
         a->setPosition( Vec3<float>(6, 3, 0) );
         a->setMass( 2 );

         b = new Particle;
         b->setPosition( Vec3<float>(-6, 3, 0) );
         b->setMass( 1 );

         c = new Particle;
         c->setPosition( Vec3<float>(-6, 3, -6) );
         c->setMass( 1.5 );

         Spring* spring = new Spring;
         s.add( a );
         s.add( b );
         s.add( spring );
         if (ignore) ignore->ignore( a );
         if (ignore) ignore->ignore( b );
         spring->setParticles( a, b );
         spring->setSpringConstant( 5.0 );
         spring->setDampeningConstant( 0.5 );
         spring->setRestLength( 5 );

         Spring* spring2 = new Spring;
         s.add( c );
         s.add( spring2 );
         if (ignore) ignore->ignore( c );
         spring2->setParticles( a, c );
         spring2->setSpringConstant( 20.0 );
         spring2->setDampeningConstant( 2 );
         spring2->setRestLength( 5 );

         Spring* spring3 = new Spring;
         s.add( spring3 );
         spring3->setParticles( b, c );
         spring3->setSpringConstant( 20.0 );
         spring3->setDampeningConstant( 1.5 );
         spring3->setRestLength( 5 );


         spring->deref();
         spring2->deref();
         spring3->deref();
      }
      
      Particle* a, *b, *c;
      virtual void step( float timeDelta )
      {
         static int when_to_start = 0;
         when_to_start++;
         
         // hack for stability upon startup.
         if (when_to_start > 20)
         {
            const float mag = 3.0f;
            velocitizer += 0.75f * timeDelta;
            if (velocitizer > 1.0f || velocitizer <= 0)
               velocitizer = 0.0f;
            Vec3<float> vel( kev::SIN( velocitizer * TWO_PI_F ) * mag, 0.0f, kev::COS( velocitizer * TWO_PI_F ) * mag );
	         a->setVelocity( vel );
         }
         
         ParticleSystem::step( timeDelta );
      }   
      float velocitizer;
};
