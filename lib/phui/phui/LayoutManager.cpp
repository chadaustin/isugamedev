/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:

#include "LayoutManager.h"
#include "Point.h"

namespace phui
{
   void
   LayoutManager::remove(const Point& point)
   {
      std::vector< std::pair<Point, Size> >::iterator itr;
      for (itr = mWidgets.begin(); itr != mWidgets.end(); ++itr)
      {
         if ((*itr).first == point)
         {
            mWidgets.erase(itr);
            return;
         }
      }
   }

}//end of namespace phui
