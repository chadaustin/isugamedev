#ifndef MW_BODY_CHANGE_EVENT_H
#define MW_BODY_CHANGE_EVENT_H

namespace mw
{
   class RigidBody;

   class BodyChangeEvent
   {
   public:
      BodyChangeEvent(RigidBody* src);

      RigidBody* getSource() const;

   private:
      RigidBody* mSource;
   };
}

#endif
