/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:

#ifndef PHUI_FLOWVERTICALCONSTRAINT_H
#define PHUI_FLOWVERTICALCONSTRAINT_H

#include "LayoutConstraint.h"

namespace phui
{
   /**
    * Layout constraint that makes a flow layout flow vertically 
    */
   class FlowVerticalConstraint : public LayoutConstraint
   {
   public:
      const std::string getType()
      {
         return "FLOW_VERTICAL";
      }
   };
}

#endif
