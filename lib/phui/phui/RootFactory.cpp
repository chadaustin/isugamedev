#include "RootFactory.h"


namespace phui {

  RootWidget* CreateRoot() {
    return new RootWidget();
  }

}
