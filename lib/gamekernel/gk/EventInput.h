#ifndef EVENT_INPUT
#define EVENT_INPUT

#include "DigitalInput.h"

class EventInput : public DigitalInput
{
public:
   virtual ~EventInput() {}
   
   virtual EdgeTriggerState edgeState() const
   {
      DigitalInput::EdgeTriggerState state = DigitalInput::UP;
      for (int x = 0; x < mDigitalBindings.size(); ++x)
      {
         if (state == DigitalInput::UP)
         {
            switch (mDigitalBindings[x]->edgeState())
            {
               case DigitalInput::UP: state = DigitalInput::UP; break;
               case DigitalInput::EDGE_UP: state = DigitalInput::EDGE_UP; break;
               case DigitalInput::EDGE_DOWN: state = DigitalInput::EDGE_DOWN; break;
               case DigitalInput::DOWN: state = DigitalInput::DOWN; break;
            }
         }
         else if (mDigitalBindings[x]->edgeState() == DigitalInput::DOWN)
         {
            state == DigitalInput::DOWN;
         }
         else if (mDigitalBindings[x]->edgeState() == DigitalInput::EDGE_DOWN &&
                  state != DigitalInput::DOWN)
         {
            state == DigitalInput::EDGE_DOWN;
         }
      }
      return state;
   }
   
   void bind( Input* in_put )
   {
      if (in_put)
      {
         DigitalInput* dig = dynamic_cast<DigitalInput*>( in_put );
         if (dig)
            mDigitalBindings.push_back( dig );
         AnalogInput* ana = dynamic_cast<AnalogInput*>( in_put );
         if (ana)
            mAnalogBindings.push_back( ana );
      }
   }
   
   std::vector< AnalogInput* > mAnalogBindings;
   std::vector< DigitalInput* > mDigitalBindings;
};

#endif
