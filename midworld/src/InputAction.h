/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:

#ifndef MW_INPUT_ACTION__H
#define MW_INPUT_ACTION__H
namespace mw
{
  
   /**
    * States of the action
    */
   enum EdgeState
   {
      DOWN, UP, EDGE_DOWN, EDGE_UP
   };
 
   /**
    * An action representing something that is input from the user
    */
   class InputAction
   {
      friend class InputManager;
   public:
      
      /**
       * Gets the ID for this action
       */
      unsigned long getID();
      /**
       * Gets the present state of this action
       * @return the state of this action
       */
      EdgeState getState();
      /**
       * Sets the state of this action
       * @param state the new state
       */
      void setState(EdgeState state);

      /**
       * Compares the ID of the objects.
       *
       * @param action the action to compare to.
       * 
       * @return true if equal, false if not
       */
      bool operator==(const InputAction& action)
      {
         return (this->mID == action.mID);
      }
   private:
      /**
       * Use the InputManager to create these
       */
      InputAction()
         : mID(0), mState(UP)
      {
      }
      InputAction(unsigned long id)
         : mID(id), mState(UP)
      {
      }
      /**
       * Sets the ID for this action
       */
      void setID(unsigned long id);
      ///The unique ID for this action
      unsigned long mID;
      ///The present state of this action
      EdgeState mState;
   };


}//end of namespace mw

#endif
