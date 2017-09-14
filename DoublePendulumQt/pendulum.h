#ifndef PENDULUM_H
#define PENDULUM_H

#include <iostream>

struct Pendulum {
    /**
     All measurements are in meters, kilograms, and radians
     */
    Pendulum (double length=1.0, double mass=1.0, double theta_i=0.0, double vel_i=0.0);
    friend std::ostream& operator<<(std::ostream& os, const Pendulum& p);
    double length;
    double mass;
    double theta;
    double velocity;
};

std::ostream& operator<<(std::ostream& os, const Pendulum& p);

#endif // PENDULUM_H
