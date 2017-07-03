//
//  Pendulum.cpp
//  DoublePendulum
//
//  Created by Ben Hoberman on 7/1/17.
//  Copyright © 2017 Ben Hoberman LLC. All rights reserved.
//

#include "Pendulum.hpp"
#include <iostream>

Pendulum::Pendulum(double width, double length, double mass, double theta_i, double vel_i) {
    this->width = width;
    this->length = length;
    this->mass = mass;
    this->theta = theta_i;
    this->velocity = vel_i;
}
