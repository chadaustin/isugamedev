#ifndef CLIENT_GARAGE_STATE_H
#define CLIENT_GARAGE_STATE_H


#include <phui/phui.h>
#include "State.h"
#include "Scene.h"


namespace client {

   class GarageState : public State
                            , phui::ActionListener
                            , phui::ListSelectionListener
   {
   public:
      GarageState();
      ~GarageState();

      void draw();
      void update(BrothaApp* app, int elapsedTime);
      void onKeyPress(SDLKey sym, bool down);
      void onMousePress(Uint8 button, bool down, int x, int y);
      void onMouseMove(int x, int y);

      virtual void onAction(const phui::ActionEvent& evt);
      virtual void onListSelection(const phui::ListSelectionEvent& evt);
   private:
      phui::RootWidget* mRoot;
      phui::Window* mMainWnd;
      phui::Button* mDealerBtn;
      phui::Button* mChopShopBtn;
      phui::Button* mJoinGameBtn;

      phui::Window* mDealerWnd;
      phui::ListBox* mCarsList;
      phui::ListBox* mCarsOwnedList;
      phui::Button* mBuyBtn;
      phui::Button* mSellBtn;

      phui::Window* mChopShopWnd;
   };

}


#endif
