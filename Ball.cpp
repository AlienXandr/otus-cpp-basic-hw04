#include "Ball.hpp"
#include <cmath>

Ball::Ball(Point& center, Velocity& velocity, double radius, Color& color,
           bool isCollidable)
    : center_{center}, velocity_{velocity}, radius_{radius}, color_{color},
      isCollidable_{isCollidable} {
    //    center_ = center;
    //    velocity_ = velocity;
    //    radius_ = radius;
    //    color_ = color;
    //    isCollidable_ = isCollidable;
    mass_ = M_PI * std::pow(radius, 3) * 4. / 3.;
}

/**
 * Задает скорость объекта
 * @param velocity новое значение скорости
 */
void Ball::setVelocity(const Velocity& velocity) {
    // TODO: место для доработки
    velocity_ = velocity;
}

/**
 * @return скорость объекта
 */
Velocity Ball::getVelocity() const {
    // TODO: место для доработки
    return velocity_;
}

/**
 * @brief Выполняет отрисовку объекта
 * @details объект Ball абстрагирован от конкретного
 * способа отображения пикселей на экране. Он "знаком"
 * лишь с интерфейсом, который предоставляет Painter
 * Рисование выполняется путем вызова painter.draw(...)
 * @param painter контекст отрисовки
 */
void Ball::draw(Painter& painter) const {
    // TODO: место для доработки
    painter.draw(center_, radius_, color_);
}

/**
 * Задает координаты центра объекта
 * @param center новый центр объекта
 */
void Ball::setCenter(const Point& center) {
    // TODO: место для доработки
    center_ = center;
}

/**
 * @return центр объекта
 */
Point Ball::getCenter() const {
    // TODO: место для доработки
    return center_;
}

/**
 * @brief Возвращает радиус объекта
 * @details обратите внимание, что метод setRadius()
 * не требуется
 */
double Ball::getRadius() const {
    // TODO: место для доработки
    return radius_;
}

/**
 * @brief Возвращает массу объекта
 * @details В нашем приложении считаем, что все шары
 * состоят из одинакового материала с фиксированной
 * плотностью. В этом случае масса в условных единицах
 * эквивалентна объему: PI * radius_^3 * 4. / 3.
 */
double Ball::getMass() const {
    // TODO: место для доработки
    return mass_;
}

bool Ball::getIsCollidable() const {
    return isCollidable_;
}