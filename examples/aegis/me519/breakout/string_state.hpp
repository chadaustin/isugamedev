#ifndef STRING_STATE_HPP
#define STRING_STATE_HPP


#include <string>
#include "state.hpp"


struct StringState : State {
  StringState(const std::string& text);

  void draw();

private:
  std::string m_text;
};


#endif
