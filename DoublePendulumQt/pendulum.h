#ifndef PENDULUM_H
#define PENDULUM_H

#include <iostream>

struct Pendulum {
    /**
     All measurements are in meters, kilograms, and radians
     */
    Pendulum (double width, double length, double mass, double theta_i, double vel_i);
    friend std::ostream& operator<<(std::ostream& os, const Pendulum& p);
    double width;
    double length;
    double mass;
    double theta;
    double velocity;
};

std::ostream& operator<<(std::ostream& os, const Pendulum& p);

#endif // PENDULUM_H
