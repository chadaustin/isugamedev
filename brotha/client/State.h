#ifndef CLIENT_STATE_H
#define CLIENT_STATE_H

namespace client {

   class BrothaApp;

   class State {
   public:
      virtual ~State() { }
      virtual void draw() = 0;
      virtual void update(BrothaApp* app, int elapsedTime) = 0;
   };

}

#endif
