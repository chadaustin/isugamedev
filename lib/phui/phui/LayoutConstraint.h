/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:

#ifndef PHUI_LAYOUTCONSTRAINT_H
#define PHUI_LAYOUTCONSTRAINT_H

#include <string>

namespace phui
{
   /**
    * Represents a layout constraint.  This is used to create layout constraint
    * classes which can then be checked against by layout managers
    */
   class LayoutConstraint
   {
   public:
      
      /**
       * Gets the type of layout constraint represented by this class
       *
       * @return     the name of this layout constraint
       */
      virtual const std::string& getType() = 0;

   };
}//end of namespace phui

#endif
