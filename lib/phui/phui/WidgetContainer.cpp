#include <algorithm>
#include <functional>
#include "WidgetContainer.h"


namespace phui {

  WidgetContainer::WidgetContainer() {
  }

  WidgetContainer::~WidgetContainer() {
  }

  void
  WidgetContainer::addWidget(Widget* widget) {
    mWidgets.push_back(widget);
  }

  void
  WidgetContainer::draw() {
    std::for_each(mWidgets.begin(), mWidgets.end(), mem_fun(&Widget::draw));
  }

}
