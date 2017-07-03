//
//  Pendulum.hpp
//  DoublePendulum
//
//  Created by Ben Hoberman on 7/1/17.
//  Copyright © 2017 Ben Hoberman LLC. All rights reserved.
//

#ifndef Pendulum_hpp
#define Pendulum_hpp
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

#endif /* Pendulum_hpp */
