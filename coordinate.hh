//
// Created by Robert on 5/19/17.
//

#ifndef NAVIGATIONSYSTEM_COORDINATE_HH
#define NAVIGATIONSYSTEM_COORDINATE_HH

#include <ostream>

class Coordinate {
public:
  Coordinate(long double x = 0, long double y = 0, long double z = 0);

  long double x;
  long double y;
  long double z;

  bool operator==(const Coordinate &rhs) const;

  bool operator!=(const Coordinate &rhs) const;

  Coordinate &operator+=(const Coordinate &rhs);

  friend Coordinate operator+(Coordinate lhs, const Coordinate &rhs);

  friend long double operator*(Coordinate lhs, const Coordinate &rhs);
  Coordinate &operator*=(const Coordinate &rhs);

  friend Coordinate operator*(Coordinate lhs, const long double rhs);
  Coordinate &operator*=(const long double rhs);


  friend Coordinate operator/(Coordinate lhs, const long double rhs);
  Coordinate &operator/=(const long double rhs);

  Coordinate &operator-=(const Coordinate &rhs);

  friend Coordinate operator-(Coordinate lhs, const Coordinate &rhs);

  friend std::ostream &operator<<(std::ostream &os, const Coordinate &coordinate);

  long double euclideanDistance(const Coordinate &rhs) const;


  long double norm() const;

  Coordinate normalized() const;
  Coordinate reflected(const Coordinate& other) const;
  
  Coordinate squared() const;

};

#endif //NAVIGATIONSYSTEM_COORDINATE_HH
