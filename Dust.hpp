#pragma once
#include "Painter.hpp"
#include "Point.hpp"
#include "Velocity.hpp"

class Dust {
  public:
    Dust(Point& center, Velocity& velocity, double radius, Color color);
    void draw(Painter& painter) const;
    void setCenter(const Point& center);
    Point getCenter() const;
    void setVelocity(const Velocity& velocity);
    Velocity getVelocity() const;
    void setRadius(double radius);
    double getRadius() const;

  private:
    Point center_;
    Velocity velocity_;
    double radius_;
    Color color_;
};
