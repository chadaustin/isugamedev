#ifndef LIGHTXML_H
#define LIGHTXML_H


#include <stdlib.h>
#include <string.h>


namespace lightxml {

  template<typename T>
  class allocator {
  public:
    static T* allocate(int size) {
      return reinterpret_cast<T*>(::malloc(size * sizeof(T)));
    }
    static T* reallocate(T* ptr, int size) {
      return reinterpret_cast<T*>(::realloc(ptr, size * sizeof(T)));
    }
    static void free(T* ptr) {
      ::free(ptr);
    }
  };

  // So we don't incur a dependency on the standard C++ library, define our own
  // string class.  This is supposed to be a lightweight library!  However,
  // this class should be relatively source-compatible with std::string, so
  // at some point it can be replaced with |using std::string;|.
  class string : private allocator<char> {
  public:
    string(char c) {
      m_data = allocate(2);
      m_data[0] = c;
      m_data[1] = 0;
    }
    string(const char* c = "") {
      m_data = allocate(strlen(c) + 1);
      strcpy(m_data, c);
    }
    string(const string& s) {
      m_data = allocate(s.length() + 1);
      strcpy(m_data, s.c_str());
    }
    string(const char* begin, const char* end) {
      int length = end - begin;
      m_data = allocate(length + 1);
      m_data[length] = 0;
      memcpy(m_data, begin, length * sizeof(char));
    }
    ~string() {
      free(m_data);
    }
	   
    int length() const { return size(); }
    int size() const { return strlen(m_data); }
    const char* c_str() const { return m_data; }

    string& operator=(const string& rhs) {
      m_data = reallocate(m_data, rhs.length() + 1);
      strcpy(m_data, rhs.c_str());
      return *this;
    }

    string& operator+=(char c) {
      int length = size();
      m_data = reallocate(m_data, length + 2);
      m_data[length] = c;
      m_data[length + 1] = 0;
      return *this;
    }

  private:
    char* m_data;
  };

  class IParserHandler {
  public:
    virtual bool handleBeginTag(const char* name, const char** attributes) = 0;
    virtual bool handleEndTag(const char* name) = 0;
    virtual bool handleCharacterData(const char* data) = 0;
  };

  class Parser {
  public: // public methods
    Parser(IParserHandler* handler);
    bool parse(const char* s);

  private: // private types
    struct Token {

      template<typename T>
      Token(T value_) : value(value_), next(0) {
      }

      string value;
      Token* next;
    };

  private: // private methods
    static Token* tokenize(const char* s, bool& failure);
    static void deleteList(Token* t);
    bool parse(Token* t);

  private: // private data
    IParserHandler* m_handler;

    Token* m_current;
  };

}

#endif
