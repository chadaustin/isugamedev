#ifndef PS_OPERATOR_H
#define PS_OPERATOR_H
#include <vector>

#include "Fizix/Operator.h"
#include "Fizix/Memory.h"

namespace ani
{
   template <class __EntityType>
   class DynamicSystem;
   
   template<class __EntityType>
   class Operator : public ani::Memory
   {
   public:
      Operator()
      {
      }
      virtual ~Operator() {}
      virtual void exec( ani::DynamicSystem<__EntityType>& ps, float timeDelta ) = 0;
   };
};

#endif
