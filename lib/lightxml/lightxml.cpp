#include <ctype.h>
#include "lightxml.h"


namespace lightxml {

  Parser::Parser(IParserHandler* handler) {
    m_handler = handler;
  }

  bool
  Parser::parse(const char* s) {

    // tokenize the input stream
    bool failure = false;
    Token* begin = tokenize(s, failure);
    if (failure) {
      deleteList(begin);
      return false;
    }

    bool result = parse(begin);
    deleteList(begin);
    return result;
  }

  Parser::Token*
  Parser::tokenize(const char* s, bool& failure) {

    Token* head = 0;
    Token* last = 0;

    while (*s) {

      // skip spaces
      while (::isspace(*s)) {
	++s;
      }
      if (!*s) {
	break;
      }

      // single-character punctuators
      if (*s == '>' || *s == '<' || *s == '=') {
	last = (last ? last->next : head) = new Token(*s++);
	continue;
      }

      // string literal
      if (*s == '"') {
	const char* t = s + 1;
	while (*t && *t != '"') {
	  ++t;
	}
	if (!*t) {
	  break;
	}

	string value(s + 1, t);
	last = (last ? last->next : head) = new Token(value);
	s = t + 1;
	continue;
      }

      // identifiers
      if (isalnum(*s) || *s == '_') {
	const char* t = s + 1;  // we already know that *s is valid
	while (isalnum(*t) || *t == '_') {
	  ++t;
	}

	string value(s, t);
	last = (last ? last->next : head) = new Token(value);
	s = t;
	continue;
      }

      // if we got here, invalid tokens?
      failure = true;
      break;
    }

    return head;
  }

  void
  Parser::deleteList(Token* t) {
    Token* p = t;
    while (p) {
      Token* kill = p;
      p = p->next;
      delete kill;
    }
  }

  bool
  Parser::parse(Token* start) {
    m_current = start;

    // XXXaegis
    // Insert recursive-descent parser here.
    // Character data won't work right now, because the tokenizer
    // doesn't understand it.
    return false;
  }

}
