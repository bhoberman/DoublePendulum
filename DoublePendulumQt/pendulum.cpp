#include "pendulum.h"

#include <iostream>

Pendulum::Pendulum (double length, double mass, double theta_i, double vel_i) {
    this->length = length;
    this->mass = mass;
    this->theta = theta_i;
    this->velocity = vel_i;
}

std::ostream& operator<<(std::ostream& os, const Pendulum& p) {
    return os << "(" << p.theta << ", " << p.velocity << ")";
}
