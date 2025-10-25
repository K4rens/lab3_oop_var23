#ifndef FIGURES_HPP
#define FIGURES_HPP


#include <vector>
#include <iostream>


enum class pointsCountFigure {
  triangle = 3,
  hexagon = 6,
  octagon = 8
};


struct Point {
  double x;
  double y;
};


class Figure {
  protected:
    std::vector<struct Point> points;

    Figure(const pointsCountFigure psC);
    Figure(const std::vector<struct Point> &ps, const pointsCountFigure psC);
  
  public:
    struct Point center() const;
    double square() const;

    Figure &operator=(Figure &&other) noexcept;
    Figure &operator=(const Figure &other);

    friend std::ostream &operator<<(std::ostream &out, const Figure &f);
    friend bool operator==(const Figure &l, const Figure &r);
    friend std::istream &operator>>(std::istream &in, Figure &f);

    class EmptyFigureException {};
    class IncorrectPointsCountException {};
};


class Triangle: public Figure {
  public:
    Triangle();
    Triangle(const std::vector<struct Point> &ps);
};


class Hexagon: public Figure {
  public:
    Hexagon();
    Hexagon(const std::vector<struct Point> &ps);
};


class Octagon: public Figure {
  public:
    Octagon();
    Octagon(const std::vector<struct Point> &ps);
};


#endif
