#pragma once
#include "Painter.hpp"
#include "Point.hpp"
#include "Velocity.hpp"

class Ball {
  public:
    Ball(Point& center, Velocity& velocity, double radius, Color& color,
         bool isCollidable);
    void setVelocity(const Velocity& velocity);
    Velocity getVelocity() const;
    void draw(Painter& painter) const;
    void setCenter(const Point& center);
    Point getCenter() const;
    double getRadius() const;
    double getMass() const;
    bool getIsCollidable() const;

  private:
    Point center_;
    Velocity velocity_;
    double radius_;
    double mass_;
    Color color_;
    bool isCollidable_;
};
