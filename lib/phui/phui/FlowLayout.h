/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:

#ifndef PHUI_FLOWLAYOUT_H
#define PHUI_FLOWLAYOUT_H

#include "LayoutConstraint.h"
#include "LayoutManager.h"
#include "Point.h"
#include "Size.h"
#include "WidgetContainer.h"

namespace phui
{
   class FlowLayout : public LayoutManager
   {
   public:
      
      /**
       * Constructor
       *
       * @param   container   the widget container to manage
       * @param   constraint  the layout contstraint to follow
       */
      FlowLayout(WidgetContainer* container, LayoutConstraint* constraint) 
         : LayoutManager(container, constraint), mCurrentWidth(0), \
           mCurrentMaxWidth(0), mCurrentHeight(0), mCurrentMaxHeight(0)
      {
         
      }
      
      /**
       * Adds a widget's specifications to this layout manager
       *
       * @param   point       the point where the widget will be added
       * @param   size        the size of the widget to be added
       */
      virtual void add(const Point& point, const Size& size);
      
      /**
       * Removes a widget's specifications from this layout manager
       *
       * @param   point       the point of the widget to be removed
       */
      virtual void remove(const Point& point)
      {
         //TODO: Resize
         LayoutManager::remove(point);
      }

   private:
      
      ///Current Width 
      int mCurrentWidth;
      ///Current Maximum Width 
      int mCurrentMaxWidth;
      ///Current Height 
      int mCurrentHeight;
      ///Current Maximum Height
      int mCurrentMaxHeight;
      
   };
}

#endif
