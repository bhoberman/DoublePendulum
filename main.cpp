

#include <SFML/Graphics.hpp>
#include <cmath>
#include <Eigen/Dense>
#include <iostream>
#include "Pendulum.hpp"

constexpr double g = 9.807;
//Conversion from meters to pixels
constexpr double M_TO_PX = 1500;
constexpr int X_OFFSET = 400;

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

double S1(Eigen::Vector2d position, Eigen::Vector2d velocity, double lengths) {
    using std::sin;
    using std::cos;
    double result = 0;
    result += 3*velocity(1)*sin(position(0) - position(1))*(velocity(0) - velocity(1));
    result -= 3*velocity(0)*velocity(1)*sin(position(0) - position(1));
    result -= 9*g*sin(position(0))/lengths;
    return result;
}

double S2(Eigen::Vector2d position, Eigen::Vector2d velocity, double lengths) {
    using std::sin;
    using std::cos;
    double result = 0;
    result += 3*velocity(0)*sin(position(0) - position(1))*(velocity(0) - velocity(1));
    result += 3*velocity(0)*velocity(1)*sin(position(0) - position(1));
    result -= 3*g*sin(position(1))/lengths;
    return result;
}

Eigen::Vector2d calculateAcceleration(Eigen::Vector2d position, Eigen::Vector2d velocity, double lengths) {
    using Eigen::Vector2d;
    using std::sin;
    using std::cos;
    Vector2d result;
    result(0) = (2*S1(position, velocity, lengths) - 3*S2(position, velocity, lengths))/(16 + 9*cos(position(0) - position(1)));
    result(1) = (8*S2(position, velocity, lengths) - 3*S1(position, velocity, lengths)*cos(position(0) - position(1)))/(16 - 8*cos(position(0) - position(1)));
    return result;
}

void incrementPendulums(Pendulum& anchored, Pendulum& free, double dt) {
    using Eigen::Vector2d;
    Vector2d initialPos(2), initialVel(2);
    initialPos(0) = anchored.theta;
    initialPos(1) = free.theta;
    initialVel(0) = anchored.velocity;
    initialVel(1) = free.velocity;
    
    Vector2d k0 = dt*initialVel;
    Vector2d l0 = dt*calculateAcceleration(initialPos, initialVel, anchored.length);
    Vector2d k1 = dt*(initialVel + l0/2.0);
    Vector2d l1 = dt*calculateAcceleration(initialPos + k0/2.0, initialVel + l0/2.0, anchored.length);
    Vector2d k2 = dt*(initialVel + l1/2.0);
    Vector2d l2 = dt*calculateAcceleration(initialPos + k1/2.0, initialVel + l1/2.0, anchored.length);
    Vector2d k3 = dt*(initialVel + l2);
    Vector2d l3 = dt*calculateAcceleration(initialPos + k2, initialVel + l2, anchored.length);
    
    Vector2d newPos(2), newVel(2);
    newPos = initialPos + dt/6.0*(k0 + 2.0*k1 + 2.0*k2 + k3);
    newVel = initialVel + dt/6.0*(l0 + 2.0*l1 + 2.0*l2 + l3);
    
    anchored.theta = newPos(0);
    anchored.velocity = newVel(0);
    free.theta = newPos(1);
    free.velocity = newPos(1);
}

int main(int, char const**)
{
    using std::sin;
    using std::cos;
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(960, 700), "Double Pendulum");
    
    Pendulum p1(0.005, 0.15, 0.3, M_PI_4 - 0.1, 0.0), p2(0.005, 0.15, 0.3, M_PI_4 - 0.1, 0.0);
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
        incrementPendulums(p1, p2, static_cast<double>(dt.asSeconds())*6);
        
        //Draw the pendulums
        sf::RectangleShape rect1(sf::Vector2f(M_TO_PX*p1.width, M_TO_PX*p1.length));
        sf::RectangleShape rect2(sf::Vector2f(M_TO_PX*p2.width, M_TO_PX*p2.length));
        //Subtract 90 degrees because of difference in definition of where theta=0 is
        rect1.setOrigin(M_TO_PX*p1.width/2.0, M_TO_PX*p1.length);
        rect2.setOrigin(M_TO_PX*p2.width/2.0, M_TO_PX*p1.length);
        //NOTE: These will have to be rewritten when I add support for different lengths
        rect1.setPosition(X_OFFSET, 0);
        rect2.setPosition(X_OFFSET + M_TO_PX*p1.length*sin(p1.theta), M_TO_PX*p1.length*cos(p1.theta));
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
