#ifndef PHUI_CHECK_BOX_H
#define PHUI_CHECK_BOX_H


#include "phuiCommon.h"
#include <string>
#include "Widget.h"


namespace phui {

   class CheckBox : public Widget {
   public:
      CheckBox(bool checked = false);

      void draw();

      void check();
      void uncheck();

      bool isChecked();

      void onMouseDown(InputButton button, const Point& p);

   private:
      bool mIsChecked;
   };

}


#endif
