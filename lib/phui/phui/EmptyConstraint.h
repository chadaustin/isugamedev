/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:

#ifndef PHUI_EMPTYCONSTRAINT_H
#define PHUI_EMPTYCONSTRAINT_H

#include "LayoutConstraint.h"

namespace phui
{
   /**
    * This class is an empty constraint that places no constraints on a manger
    */
   class EmptyConstraint : public LayoutConstraint
   {
   public:

      virtual const std::string getType()
      {
         return "EMPTY_CONSTRAINT";
      }
   };

}//end of namespace phui

#endif
