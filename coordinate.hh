//
// Created by Robert on 5/19/17.
//

#ifndef NAVIGATIONSYSTEM_COORDINATE_HH
#define NAVIGATIONSYSTEM_COORDINATE_HH

#include <ostream>

class Coordinate {
public:
  Coordinate(double x = 0, double y = 0, double z = 0);

  double x;
  double y;
  double z;

  bool operator==(const Coordinate &rhs) const;

  bool operator!=(const Coordinate &rhs) const;

  Coordinate &operator+=(const Coordinate &rhs);

  friend Coordinate operator+(Coordinate lhs, const Coordinate &rhs);

  friend double operator*(Coordinate lhs, const Coordinate &rhs);
  Coordinate &operator*=(const Coordinate &rhs);

  friend Coordinate operator*(Coordinate lhs, const double rhs);
  Coordinate &operator*=(const double rhs);


  friend Coordinate operator/(Coordinate lhs, const double rhs);
  Coordinate &operator/=(const double rhs);

  Coordinate &operator-=(const Coordinate &rhs);

  friend Coordinate operator-(Coordinate lhs, const Coordinate &rhs);

  friend std::ostream &operator<<(std::ostream &os, const Coordinate &coordinate);

  double euclideanDistance(const Coordinate &rhs) const;


  double norm() const;

  Coordinate normalized() const;
  Coordinate reflected(const Coordinate& other) const;
  
  Coordinate squared() const;

};

#endif //NAVIGATIONSYSTEM_COORDINATE_HH
