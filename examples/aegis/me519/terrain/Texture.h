#ifndef TEXTURE_H
#define TEXTURE_H


#include <GL/glut.h>
#include <exception>
#include <string>


class TextureException : public std::exception {
public:
  TextureException(const std::string& what) {
    mWhat = what;
  }

  ~TextureException() throw() {
  }

  const char* what() const throw() {
    return mWhat.c_str();
  }

private:
  std::string mWhat;
};


class Texture {
public:
  Texture(const char* filename);
  ~Texture();

  void bind();

private:
  GLuint m_texture;
};


#endif
