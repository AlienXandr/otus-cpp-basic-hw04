#include "Physics.hpp"
#include "Dust.hpp"
#include "get_random_value/get_random_value.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>

double dot(const Point& lhs, const Point& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

Physics::Physics(double timePerTick) : timePerTick{timePerTick} {}

void Physics::setWorldBox(const Point& topLeft, const Point& bottomRight) {
    this->topLeft = topLeft;
    this->bottomRight = bottomRight;
}

void Physics::update(std::vector<Ball>& balls, std::vector<Dust>& dusts,
                     const size_t ticks) const {

    for (size_t i = 0; i < ticks; ++i) {
        move(balls);
        collideWithBox(balls);
        collideBalls(balls, dusts);
        move(dusts);
    }
}

void Physics::collideBalls(std::vector<Ball>& balls,
                           std::vector<Dust>& dusts) const {
    for (auto a = balls.begin(); a != balls.end(); ++a) {
        if (!a->getIsCollidable()) {
            continue;
        }
        for (auto b = std::next(a); b != balls.end(); ++b) {
            if (!b->getIsCollidable()) {
                continue;
            }
            const double distanceBetweenCenters2 =
                distance2(a->getCenter(), b->getCenter());
            const double collisionDistance = a->getRadius() + b->getRadius();
            const double collisionDistance2 =
                collisionDistance * collisionDistance;

            if (distanceBetweenCenters2 < collisionDistance2) {
                processCollision(*a, *b, distanceBetweenCenters2);
                createDustExplosion(*a, *b, dusts);
            }
        }
    }
}

void Physics::collideWithBox(std::vector<Ball>& balls) const {
    for (Ball& ball : balls) {
        if (!ball.getIsCollidable()) {
            continue;
        }
        const Point p = ball.getCenter();
        const double r = ball.getRadius();
        // определяет, находится ли v в диапазоне (lo, hi) (не включая границы)
        auto isOutOfRange = [](double v, double lo, double hi) {
            return v < lo || v > hi;
        };

        if (isOutOfRange(p.x, topLeft.x + r, bottomRight.x - r)) {
            Point vector = ball.getVelocity().vector();
            vector.x = -vector.x;
            ball.setVelocity(vector);
        } else if (isOutOfRange(p.y, topLeft.y + r, bottomRight.y - r)) {
            Point vector = ball.getVelocity().vector();
            vector.y = -vector.y;
            ball.setVelocity(vector);
        }
    }
}

void Physics::move(std::vector<Ball>& balls) const {
    for (Ball& ball : balls) {
        Point newPos =
            ball.getCenter() + ball.getVelocity().vector() * timePerTick;
        ball.setCenter(newPos);
    }
}
void Physics::move(std::vector<Dust>& dusts) const {
    for (Dust& dust : dusts) {
        Point newPos =
            dust.getCenter() + dust.getVelocity().vector() * timePerTick;
        dust.setCenter(newPos);

        double newRadius = dust.getRadius() - 0.05;
        if (newRadius > 0) {
            dust.setRadius(newRadius);
        }
    }
    // Очистка массива
    dusts.erase(
        std::remove_if(dusts.begin(), dusts.end(),
                       [](Dust const& dust) { return dust.getRadius() <= 0; }),
        dusts.end());
}

void Physics::processCollision(Ball& a, Ball& b,
                               double distanceBetweenCenters2) const {
    // нормированный вектор столкновения
    const Point normal =
        (b.getCenter() - a.getCenter()) / std::sqrt(distanceBetweenCenters2);

    // получаем скорость в векторном виде
    const Point aV = a.getVelocity().vector();
    const Point bV = b.getVelocity().vector();

    // коэффициент p учитывает скорость обоих мячей
    const double p =
        2 * (dot(aV, normal) - dot(bV, normal)) / (a.getMass() + b.getMass());

    // задаем новые скорости мячей после столкновения
    a.setVelocity(Velocity(aV - normal * p * a.getMass()));
    b.setVelocity(Velocity(bV + normal * p * b.getMass()));
}

void Physics::createDustExplosion(Ball& a, Ball& b,
                                  std::vector<Dust>& dusts) const {
    double x1, x2, y1, y2, radius;
    if (a.getCenter().x < b.getCenter().x) {
        x1 = a.getCenter().x;
        x2 = b.getCenter().x;
        radius = a.getRadius();
    } else {
        x1 = b.getCenter().x;
        x2 = a.getCenter().x;
        radius = b.getRadius();
    }
    if (a.getCenter().y < b.getCenter().y) {
        y1 = a.getCenter().y;
        y2 = b.getCenter().y;
    } else {
        y1 = b.getCenter().y;
        y2 = a.getCenter().y;
    }
    double angle = std::atan2((y2 - y1), (x2 - x1));

    double x = std::cos(angle) * radius + x1;
    double y = std::sin(angle) * radius + y1;
    Point center(x, y);
    std::srand(std::time(nullptr));

    double step = M_PI * 2 / 9;
    for (double ang = 0; ang < M_PI * 2; ang += step) {
        Velocity velocity(300, ang);
        Dust dust(center, velocity, get_random_value(15, 50),
                  Color(get_random_value(1, 100) / 100.,
                        get_random_value(1, 100) / 100.,
                        get_random_value(1, 100) / 100.));
        dusts.push_back(dust);
    }
}