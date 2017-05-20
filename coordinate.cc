//
// Created by Robert on 5/19/17.
//
#include <math.h>
#include "coordinate.hh"

Coordinate::Coordinate(long double x, long double y, long double z)
    : x(x), y(y), z(z) {}

bool Coordinate::operator==(const Coordinate &rhs) const {
    return x == rhs.x &&
        y == rhs.y &&
	z == rhs.z;
}

bool Coordinate::operator!=(const Coordinate &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Coordinate &coordinate) {
    os << "[" << coordinate.x << "," << coordinate.y << "," << coordinate.z << "]";
    return os;
}

Coordinate &Coordinate::operator+=(const Coordinate &rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
}
Coordinate operator+(Coordinate lhs, const Coordinate &rhs) {
    lhs += rhs;
    return lhs;
}
Coordinate &Coordinate::operator-=(const Coordinate &rhs) {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
}
long double operator*(Coordinate lhs, const Coordinate &rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

Coordinate &Coordinate::operator*=(const Coordinate &rhs) {
    x *= rhs.x;
    y *= rhs.y;
    z *= rhs.z;
    return *this;
}

Coordinate operator*(Coordinate lhs, const long double rhs) {
	lhs *= rhs;
	return lhs;
}

Coordinate &Coordinate::operator*=(const long double rhs) {
	x *= rhs;
	y *= rhs;
	z *= rhs;
	return *this;
}


Coordinate operator/(Coordinate lhs, const long double rhs) {
	lhs /= rhs;
	return lhs;
}

Coordinate &Coordinate::operator/=(const long double rhs) {
	x /= rhs;
	y /= rhs;
	z /= rhs;
	return *this;
}

Coordinate operator-(Coordinate lhs, const Coordinate &rhs) {
    lhs -= rhs;
    return lhs;
}
long double Coordinate::euclideanDistance(const Coordinate &rhs) const {
    return (long double) sqrt(pow(x + rhs.x, 2) + pow(y + rhs.y, 2));
}

long double Coordinate::norm() const {
	return sqrt(x*x + y*y + z*z);
}

Coordinate Coordinate::normalized() const {
	Coordinate ret(x,y,z);
	ret /= ret.norm();
	return ret;
}
Coordinate Coordinate::reflected(const Coordinate& other) const {
	Coordinate norm_other = other.normalized();
	return *this - (*this * other) * other * 2;
}

Coordinate Coordinate::squared() const {
	return *this * *this;
}

