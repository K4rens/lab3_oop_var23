#include "../../include/figures.hpp"
#include <iostream>
#include <cmath>
#include <utility>

#define EPSILON 1e-6


Figure &Figure::operator=(const Figure &other) {
  if (this != &other) {
    points = other.points;
  }
  return *this;
}


Figure &Figure::operator=(Figure &&other) noexcept {
  if (this != &other) {
    points = std::move(other.points);
    other.points.clear();
  }
  return *this;
}


bool isGoodPoints(const struct Point a, const struct Point b, const struct Point delta) {
  const struct Point current = {fabs(a.x - b.x), fabs(a.y - b.y)};
  const bool goodX = fabs(current.x - delta.x) < EPSILON;
  const bool goodY = fabs(current.y - delta.y) < EPSILON;
  return goodX && goodY;
}


std::istream &operator>>(std::istream &in, Figure &f) {
  if (f.points.empty()) {
    throw Figure::EmptyFigureException();
  }

  struct Point p;
  for (size_t i = 0; i != f.points.size(); ++i) {
    std::cin >> p.x >> p.y;
    f.points[i] = p;
  }

  return in;
}
std::ostream &operator<<(std::ostream &out, const Figure &f) {
  for (size_t i = 0; i != f.points.size(); ++i) {
    if (i > 0) {
      std::cout << " ";
    }
    std::cout << "(" << f.points[i].x << ", " << f.points[i].y << ")";
  }

  return out;
}
bool operator==(const Figure &l, const Figure &r) {
  if (l.points.empty() || r.points.empty()) {
    throw Figure::EmptyFigureException();
  }

  if (l.points.size() != r.points.size()) {
    return false;
  }

  const struct Point normalDelta = {
    fabs(l.points[0].x - r.points[0].x),
    fabs(l.points[0].y - r.points[0].y)
  };
  
  for (size_t i = 1; i != l.points.size(); ++i) {
    if (!isGoodPoints(l.points[i], r.points[i], normalDelta)) {
      return false;
    }
  }
  return true;
}
