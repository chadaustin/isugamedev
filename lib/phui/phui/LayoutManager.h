/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:

#ifndef PHUI_LAYOUTMANAGER_H
#define PHUI_LAYOUTMANAGER_H

#include <utility>
#include <vector>
#include "LayoutConstraint.h"
#include "Size.h"
#include "Point.h"
#include "WidgetContainer.h"

namespace phui
{
   /**
    * Represents a Layout Manager for graphical components.  A Layout Manager
    * will automatically resize and move widgets to meet the constraints of the
    * layout.
    */
   class LayoutManager
   {
   public:
      
      /**
       * Constructor
       *
       * @param   container   the widget container to manage
       * @param   constraint  the layout constraint to follow
       */
      LayoutManager(WidgetContainer *container, LayoutConstraint* constraint)
         : mConstraint(constraint), mContainer(container) 
      {
      }
     
      virtual ~LayoutManager();

      /**
       * Adds a widget's specifications to this layout manager
       *
       * @param   point       the point where the widget will be added
       * @param   size        the size of the widget to be added
       */
      virtual void add(const Point& point, const Size& size)
      {
         mWidgets.push_back( std::make_pair(point, size) );
      }
      
      /**
       * Removes a widget's specifications from this layout manager
       *
       * @param   point       the point of the widget to be removed
       */
      virtual void remove(const Point& point);

      /**
       * Checks to see if the current set of widgets is valid within the
       * constraints of this manager
       *
       * @return     true if the set of widgets is valid, false otherwise
       */
      virtual bool isValid() const
      {
         return true;
      }

      /**
       * Resizes a set of widgets to make it valid within the constraints of
       * this layout manager
       */
      virtual void resize() const
      {
         return;
      }
      
   protected:
      ///The layout constraint to follow
      LayoutConstraint* mConstraint;
      ///The container being managed by this layout manager
      WidgetContainer* mContainer;
      ///The points and sizes of all widgets that are in this layout manager
      std::vector<std::pair< Point, Size > > mWidgets;
   private:
      
   };
   

}//end of namespace phui

#endif
