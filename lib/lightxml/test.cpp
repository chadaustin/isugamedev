#include <iostream>
#include <memory>
#include <stdlib.h>
#include "lightxml.h"


class Handler : public lightxml::IParserHandler {
public:
  bool handleBeginTag(const char* name, const char** attributes) {
    return
      (strcmp(name, "element") == 0) &&
      (strcmp(attributes[0], "attrib") == 0) &&
      (strcmp(attributes[1], " value ") == 0) &&
      (attributes[2] == 0);
  }

  bool handleEndTag(const char* name) {
    return (strcmp(name, "element") == 0);
  }

  bool handleCharacterData(const char* data) {
    return (strcmp(data, " text ") == 0);
  }
};


void assertTrue(bool condition) {
  if (!condition) {
    cout << "Test failed" << endl;
    throw "failure!";
  } else {
    cout << "Test succeeded" << endl;
  }
}


void assertFalse(bool condition) {
  assertTrue(!condition);
}


bool test() {
  try {
    std::auto_ptr<Handler> handler(new Handler);
    std::auto_ptr<lightxml::Parser> parser(
      new lightxml::Parser(handler.get()));
    const char* str1 = " < element attrib = \" value \" > text < / element > ";
    const char* str2 = "<>yo";
    assertTrue(parser->parse(str1));
    assertFalse(parser->parse(str2));
    return true;
  }
  catch (...) {
    return false;
  }
}


int main() {
  bool result = test();
  if (result) {
    cout << "All tests passed" << endl;
    return EXIT_SUCCESS;
  } else {
    cout << "One or more tests failed" << endl;
    return EXIT_FAILURE;
  }
}
