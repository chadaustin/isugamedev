#include <memory>
#include <stdexcept>
#include <GL/gl.h>
#include <siren/siren.h>

class BlueState : public siren::State
{
public:
   void draw() const
   {
      glClearColor(0, 0, 1, 1);
      glClear(GL_COLOR_BUFFER_BIT);
   }

   void update(float dt)
   {}

   void onKeyPress(SDLKey sym, bool down)
   {
      if (down)
      {
         quit();
      }
   }
};

int main(int argc, char** argv)
{
   try
   {
      // Register the states
      new siren::StateCreatorImpl<BlueState>("Blue");

      std::auto_ptr<siren::Kernel> kernel(new siren::Kernel());
      kernel->start("Blue");
   }
   catch (std::runtime_error& e)
   {
      std::cerr << "Caught exception: " << e.what() << std::endl;
   }

   return 0;
}
