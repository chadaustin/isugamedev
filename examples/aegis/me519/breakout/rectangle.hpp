#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP


#include <algorithm>


// ugh, VC++ sucks
#ifdef _MSC_VER
  namespace std {

    template<typename T>
    T min(T a, T b) {
      return (a < b ? a : b);
    }

    template<typename T>
    T max(T a, T b) {
      return (a > b ? a : b);
    }

  }
#endif


struct Rectangle {
  Rectangle(double x1 = 0, double y1 = 0, double x2 = 0, double y2 = 0)
    : upper_left(Point2d(std::min(x1, x2), std::min(y1, y2)))
    , lower_right(Point2d(std::max(x1, x2), std::max(y1, y2)))
  {}

  Rectangle(const Point2d& ul, const Point2d& lr)
    : upper_left(ul)
    , lower_right(lr)
  { }

  Point2d upper_left;
  Point2d lower_right;
};


#endif
