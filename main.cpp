#include <SFML/Graphics.hpp>
#include <cmath>
#include <Eigen/Dense>
#include <iostream>
#include "Pendulum.hpp"

constexpr double g = 9.807;
constexpr double TIME_SCALE = 1.0;
constexpr double TIME_STEP = 0.01; //Tick length in seconds
//Conversion from meters to pixels
constexpr double M_TO_PX = 1500.0;
constexpr int X_OFFSET = 400;
constexpr int Y_OFFSET = 250;

double degrees(double radians) {
    return radians * 180 / M_PI;
}

/**
 Given a mathematical rotation in radians,
 with the positive x-axis being 0 and increasing counterclockwise,
 return the SFML rotation, which has the positive y-axis as 0
 and increases clockwise. Also convert to degrees.
 */
double translateRotation(double mathRotation) {
    return degrees(-mathRotation)+180.0;
}

Eigen::Vector2d calculateAcceleration(Eigen::Vector2d position, Eigen::Vector2d velocity, Eigen::Vector2d mass, Eigen::Vector2d length) {
    using std::sin;
    using std::cos;
    Eigen::Vector2d result;
    double N1, N2, D1, D2;
    //Compute the numerator for the acceleration for theta1
    //See math doc for where on Earth this comes from
    N1 = 2*length(1)*length(1)*mass(1)*velocity(1)*velocity(1)*sin(position(1) - position(0));
    N1 += 3*g*length(1)*mass(1)*cos(position(1) - position(0))*sin(position(1));
    N1 += 6*g*length(0)*mass(1)*sin(position(1));
    N1 -= 2*(g*length(1)*mass(0) + 2*g*length(1)*mass(1))*sin(position(0));
    N1 += 3*(length(0)*length(1)*mass(1)*velocity(0)*velocity(0)*cos(position(1) - position(0)) + 2*length(0)*length(0)*mass(1)*velocity(0)*velocity(0))*sin(position(1) - position(0));
    //Finally, multiply by the overall factor 3
    N1 *= 3;
    //Compute denominator for the acceleration for theta1
    D1 = 9*length(0)*length(1)*mass(1)*cos(position(1) - position(0))*cos(position(1) - position(0));
    D1 += 18*length(0)*length(0)*mass(1)*cos(position(1) - position(0));
    D1 -= 4*length(0)*length(1)*mass(0);
    
    //Compute the numerator for the acceleration for theta2
    N2 = 3*length(1)*mass(1)*velocity(1)*velocity(1)*cos(position(1) - position(0))*sin(position(1) - position(0));
    N2 += 2*length(0)*mass(0)*velocity(0)*velocity(0)*sin(position(1) - position(0));
    N2 -= 3*(g*mass(0) + 2*g*mass(1))*cos(position(1) - position(0))*sin(position(0));
    N2 += 2*g*mass(0)*sin(position(1));
    //Finally, multiply it all by 3 again
    N2 *= 3;
    
    //Compute the denominator for the acceleration for theta2
    D2 = 9*length(1)*mass(1)*cos(position(1) - position(0))*cos(position(1) - position(0));
    D2 += 18*length(0)*mass(1)*cos(position(1) - position(0));
    D2 -= 4*length(1)*mass(0);
    
    if (std::abs(D1) < 1e-9) {
        std::cout << "D1: " << D1 << std::endl;
    }
    if (std::abs(D2) < 1e-9) {
        std::cout << "D2: " << D2 << std::endl;
    }
    
    result(0) = N1/D1;
    result(1) = N2/D2;
    
    return result;
}

void incrementPendulums(Pendulum& anchored, Pendulum& free, double dt) {
    using Eigen::Vector2d;
    Vector2d initialPos, initialVel, mass, length;
    initialPos(0) = anchored.theta;
    initialPos(1) = free.theta;
    initialVel(0) = anchored.velocity;
    initialVel(1) = free.velocity;
    mass(0) = anchored.mass;
    mass(1) = free.mass;
    length(0) = anchored.length;
    length(1) = free.length;
    
    Vector2d k0 = dt*initialVel;
    Vector2d l0 = dt*calculateAcceleration(initialPos, initialVel, mass, length);
    Vector2d k1 = dt*(initialVel + l0/2.0);
    Vector2d l1 = dt*calculateAcceleration(initialPos + k0/2.0, initialVel + l0/2.0, mass, length);
    Vector2d k2 = dt*(initialVel + l1/2.0);
    Vector2d l2 = dt*calculateAcceleration(initialPos + k1/2.0, initialVel + l1/2.0, mass, length);
    Vector2d k3 = dt*(initialVel + l2);
    Vector2d l3 = dt*calculateAcceleration(initialPos + k2, initialVel + l2, mass, length);
    
    Vector2d newPos, newVel;
    newPos = initialPos + dt/6.0*(k0 + 2.0*k1 + 2.0*k2 + k3);
    newVel = initialVel + dt/6.0*(l0 + 2.0*l1 + 2.0*l2 + l3);
    
    anchored.theta = newPos(0);
    anchored.velocity = newVel(0);
    free.theta = newPos(1);
    free.velocity = newVel(1);
}

int main(int, char const**)
{
    using std::sin;
    using std::cos;
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(960, 700), "Double Pendulum");
    
    Pendulum p1(0.005, 0.15, 0.1, M_PI_2, 0.0), p2(0.005, 0.15, 0.1, M_PI_2, 0.0);
    sf::Clock deltaClock;
    
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }

        // Clear screen
        window.clear(sf::Color::White);
        
        //Increment pendulum positions
        sf::Time dt = deltaClock.restart();
        incrementPendulums(p1, p2, TIME_STEP*TIME_SCALE);
        
        //Draw the pendulums
        sf::RectangleShape rect1(sf::Vector2f(M_TO_PX*p1.width, M_TO_PX*p1.length));
        sf::RectangleShape rect2(sf::Vector2f(M_TO_PX*p2.width, M_TO_PX*p2.length));
        rect1.setOrigin(M_TO_PX*p1.width/2.0, M_TO_PX*p1.length);
        rect2.setOrigin(M_TO_PX*p2.width/2.0, M_TO_PX*p1.length);
        rect1.setPosition(X_OFFSET, Y_OFFSET);
        rect2.setPosition(X_OFFSET + M_TO_PX*p1.length*sin(p1.theta), Y_OFFSET + M_TO_PX*p1.length*cos(p1.theta));
        std::cout << dt.asSeconds() << ":" << p1.theta << "," << p2.theta << std::endl;
        rect1.setRotation(translateRotation(p1.theta));
        rect2.setRotation(translateRotation(p2.theta));
        std::cout << p1 << ", " << p2 << std::endl;
        rect1.setFillColor(sf::Color::Green);
        rect2.setFillColor(sf::Color::Blue);
        window.draw(rect1);
        window.draw(rect2);

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
