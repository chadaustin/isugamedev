#ifndef PHUI_POINT_H
#define PHUI_POINT_H


#include <iostream>


class Point {
public:
   Point()               { x = 0;   y = 0; }
   Point(int x_, int y_) { x = x_ ; y = y_; }
   Point(const Point& p) { x = p.x; y = p.y; }

   int x;
   int y;

   Point& operator+=(const Point& p) {
      x += p.x;
      y += p.y;
      return (*this);
   }
};


inline Point operator-(const Point& lhs, const Point& rhs) {
   return Point(lhs.x - rhs.x, lhs.y - rhs.y);
}

inline Point operator+(const Point& lhs, const Point& rhs) {
   return Point(lhs.x + rhs.x, lhs.y + rhs.y);
}

inline std::ostream& operator<<(std::ostream& os, const Point& p) {
   os << "(" << p.x << ", " << p.y << ")";
   return os;
}


#endif
