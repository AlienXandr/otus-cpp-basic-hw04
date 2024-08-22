#include "Dust.hpp"
#include <cmath>

Dust::Dust(Point& center, Velocity& velocity, double radius, Color color)
    : center_{center}, velocity_{velocity}, radius_{radius}, color_{color} {}

void Dust::draw(Painter& painter) const {
    painter.draw(center_, radius_, color_);
}

void Dust::setCenter(const Point& center) {
    center_ = center;
}

Point Dust::getCenter() const {
    return center_;
}

void Dust::setVelocity(const Velocity& velocity) {
    velocity_ = velocity;
}

Velocity Dust::getVelocity() const {
    return velocity_;
}

void Dust::setRadius(double radius) {
    radius_ = radius;
}

double Dust::getRadius() const {
    return radius_;
}
