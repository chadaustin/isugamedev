#include <memory>
#include <corona.h>
#include "Texture.h"
using namespace corona;


bool isPowerOfTwo(int i) {
  return (i & (i - 1)) == 0;
}


Texture::Texture(const char* filename) {
  std::auto_ptr<Image> image(OpenImage(filename, FF_AUTODETECT, PF_R8G8B8A8));
  if (!image.get()) {
    throw TextureException(
      "Could not load image '" + std::string(filename) + "'");
  }

  if (!isPowerOfTwo(image->getWidth()) || !isPowerOfTwo(image->getHeight())) {
    throw TextureException(
      "Image '" + std::string(filename) + "' has non-power-of-two dimensions");
  }

  glGenTextures(1, &m_texture);
  glBindTexture(GL_TEXTURE_2D, m_texture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,
               image->getWidth(), image->getHeight(),
               0, GL_RGBA, GL_UNSIGNED_BYTE, image->getPixels());

  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}


Texture::~Texture() {
  glDeleteTextures(1, &m_texture);
}


void
Texture::bind() {
  glBindTexture(GL_TEXTURE_2D, m_texture);
}
