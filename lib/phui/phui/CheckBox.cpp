#include "CheckBox.h"


namespace phui {

   CheckBox::CheckBox(bool checked) {
      mIsChecked = checked;      
   }

   void CheckBox::draw() {
      int width, height;
      getSize(width, height);

      glColor(getBackgroundColor());
      glBegin(GL_TRIANGLE_FAN);
      glVertex2i(0,     0     );
      glVertex2i(width, 0     );
      glVertex2i(width, height);
      glVertex2i(0,     height);
      glEnd();

      if (isChecked()) {
         glColor(getForegroundColor());
         glBegin(GL_LINES);
         glVertex2i(0,     0);
         glVertex2i(width, height);
         glVertex2i(width, 0);
         glVertex2i(0,     height);
         glEnd();
      }
      
   }

   void CheckBox::check() {
      mIsChecked = true;
   }

   void CheckBox::uncheck() {
      mIsChecked = false;
   }

   bool CheckBox::isChecked() {
      return mIsChecked;
   }

   void CheckBox::onMouseDown(InputButton button, const Point& p) {
      if (button == BUTTON_LEFT) {
         mIsChecked = !isChecked();
      }
   }

}
