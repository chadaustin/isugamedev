#include <assert.h>
#include <isym/isym.h>
#include <iostream>

int main()
{
   assert( isym::MOUSE_0 == isym::MOUSE_LEFT &&
           isym::MOUSE_1 == isym::MOUSE_MIDDLE &&
           isym::MOUSE_2 == isym::MOUSE_RIGHT && "Failed" );
   std::cout << "Passed, mouse aliases are correct" << std::endl; 

   assert( 
         isym::MOUSE_LEFT != isym::MOUSE_MIDDLE &&
         isym::MOUSE_MIDDLE != isym::MOUSE_RIGHT &&
         isym::MOUSE_RIGHT  != isym::KEY_ESCAPE &&
         isym::KEY_ESCAPE != isym::KEY_F1 &&
         isym::KEY_F1 != isym::KEY_F2 &&
         isym::KEY_F2 != isym::KEY_F3 &&
         isym::KEY_F3 != isym::KEY_F4 &&
         isym::KEY_F4 != isym::KEY_F5 &&
         isym::KEY_F5 != isym::KEY_F6 &&
         isym::KEY_F6 != isym::KEY_F7 &&
         isym::KEY_F7 != isym::KEY_F8 &&
         isym::KEY_F8 != isym::KEY_F9 &&
         isym::KEY_F9 != isym::KEY_F10 &&
         isym::KEY_F10 != isym::KEY_F11 &&
         isym::KEY_F11 != isym::KEY_F12 &&
         isym::KEY_F12 != isym::KEY_TILDE &&
         isym::KEY_TILDE != isym::KEY_MINUS &&
         isym::KEY_MINUS != isym::KEY_EQUALS &&
         isym::KEY_EQUALS != isym::KEY_BACKSPACE &&
         isym::KEY_BACKSPACE !=  isym::KEY_TAB&&
         isym::KEY_TAB !=  isym::KEY_A&&
         isym::KEY_A !=  isym::KEY_B&&
         isym::KEY_B !=  isym::KEY_C&&
         isym::KEY_C !=  isym::KEY_D&&
         isym::KEY_D !=  isym::KEY_E&&
         isym::KEY_E !=  isym::KEY_F&&
         isym::KEY_F !=  isym::KEY_G&&
         isym::KEY_G !=  isym::KEY_H&&
         isym::KEY_H !=  isym::KEY_I&&
         isym::KEY_I !=  isym::KEY_J&&
         isym::KEY_J !=  isym::KEY_K&&
         isym::KEY_K !=  isym::KEY_L&&
         isym::KEY_L !=  isym::KEY_M&&
         isym::KEY_M !=  isym::KEY_N&&
         isym::KEY_N !=  isym::KEY_O&&
         isym::KEY_O !=  isym::KEY_P&&
         isym::KEY_P !=  isym::KEY_Q&&
         isym::KEY_Q !=  isym::KEY_R&&
         isym::KEY_R !=  isym::KEY_S&&
         isym::KEY_S !=  isym::KEY_T&&
         isym::KEY_T !=  isym::KEY_U&&
         isym::KEY_U !=  isym::KEY_V&&
         isym::KEY_V !=  isym::KEY_W&&
         isym::KEY_W !=  isym::KEY_X&&
         isym::KEY_X !=  isym::KEY_Y&&
         isym::KEY_Y !=  isym::KEY_Z&&
         isym::KEY_Z !=  isym::KEY_0&&
         isym::KEY_0 !=  isym::KEY_1&&
         isym::KEY_1 !=  isym::KEY_2&&
         isym::KEY_2 !=  isym::KEY_3&&
         isym::KEY_3 !=  isym::KEY_4&&
         isym::KEY_4 !=  isym::KEY_5&&
         isym::KEY_5 !=  isym::KEY_6&&
         isym::KEY_6 !=  isym::KEY_7&&
         isym::KEY_7 !=  isym::KEY_8&&
         isym::KEY_8 !=  isym::KEY_9&&
         isym::KEY_9 != isym::KEY_SHIFT&&
         isym::KEY_SHIFT != isym::KEY_CTRL&&
         isym::KEY_CTRL != isym::KEY_ALT&&
         isym::KEY_ALT != isym::KEY_SPACE&&
         isym::KEY_SPACE != isym::KEY_OPENBRACE&&
         isym::KEY_OPENBRACE  != isym::KEY_CLOSEBRACE&&
         isym::KEY_CLOSEBRACE != isym::KEY_SEMICOLON&&
         isym::KEY_SEMICOLON  != isym::KEY_APOSTROPHE&&
         isym::KEY_APOSTROPHE != isym::KEY_COMMA&&
         isym::KEY_COMMA != isym::KEY_PERIOD&&
         isym::KEY_PERIOD != isym::KEY_SLASH&&
         isym::KEY_SLASH != isym::KEY_BACKSLASH&&
         isym::KEY_BACKSLASH  != isym::KEY_ENTER&&
         isym::KEY_ENTER != isym::KEY_INSERT&&
         isym::KEY_INSERT != isym::KEY_DELETE&&
         isym::KEY_DELETE != isym::KEY_HOME&&
         isym::KEY_HOME != isym::KEY_END&&
         isym::KEY_END != isym::KEY_PAGE_UP &&
         isym::KEY_PAGE_UP != isym::KEY_PAGE_DOWN&&
         isym::KEY_PAGE_DOWN  != isym::KEY_UP&&
         isym::KEY_UP != isym::KEY_RIGHT&&
         isym::KEY_RIGHT != isym::KEY_DOWN&&
         isym::KEY_DOWN != isym::KEY_LEFT 
         && "Failed, predefined symbols are not unique" );
   std::cout << "Passed, all predefined symbols in isym are unique" << std::endl; 

   // make sure getUID returns something different each time.
   isym::Symbol previous;
   for (int x = 0; x < 99999999; ++x)
   {
      assert( isym::getUID() != previous 
            && "Failed, isym::getUID() does not always generate different numbers." );
   }
   std::cout << "Passed, isym::getUID() generates a different value every time" << std::endl; 
   
   // @todo: make sure getUID() doesn't return the same value twice (ever)
   //        need to keep a large array to check against.
   
   return 0;
}
