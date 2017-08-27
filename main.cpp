#include <SFML/Graphics.hpp>
#include <cmath>
#include <Eigen/Dense>
#include <iostream>
#include "Pendulum.hpp"

constexpr double g = 9.807;
constexpr double TIME_STEP = 0.01; //Tick length in seconds
constexpr double SIMULATION_DURATION = 1000.0; //Simulation duration in seconds
constexpr double DISPLAY_SPEEDUP = 20.0; //Run it this many times as fast as the simulation
//Conversion from meters to pixels
constexpr double M_TO_PX = 1500.0;
constexpr int X_OFFSET = 400;
constexpr int Y_OFFSET = 250;

struct DoublePosition {
    double anchoredposition;
    double freeposition;
};

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
    Eigen::Vector2d acceleration;
    
    //These lines were taken from the SAGE output and find/replaced into this form (except substitution of ^ for pow, which was manual)
    acceleration(0) = 3*(4*g*mass(0)*sin(position(0)) + 3*g*mass(1)*sin(position(0) - 2*position(1)) + 5*g*mass(1)*sin(position(0)) + 3*length(0)*mass(1)*pow(velocity(0), 2.0)*sin(2*position(0) - 2*position(1)) + 4*length(0)*mass(1)*pow(velocity(1), 2.0)*sin(position(0) - position(1)))/(2*(-4*mass(0) + 9*mass(1)*pow(cos(position(0) - position(1)), 2.0) - 12*mass(1))*length(0));
    acceleration(1) = 3*(-2*(g*sin(position(1)) - length(0)*pow(velocity(0), 2.0)*sin(position(0) - position(1)))*(mass(0) + 3*mass(1)) + 3*(g*mass(0)*sin(position(0)) + 2*g*mass(1)*sin(position(0)) + length(0)*mass(1)*pow(velocity(1), 2.0)*sin(position(0) - position(1)))*cos(position(0) - position(1)))/((4*mass(0) - 9*mass(1)*pow(cos(position(0) - position(1)), 2.0) + 12*mass(1))*length(0));
    
    return acceleration;
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
    
    Pendulum p1(0.005, 0.15, 1, M_PI_2, 0.0), p2(0.005, 0.15, 1, M_PI_2 + .3, 0.0);
    
    //Generate all of the positions over a set time range
    std::vector<Eigen::Vector2d> positions;
    positions.push_back(Eigen::Vector2d(p1.theta, p2.theta));
    for (int i = 0; i < SIMULATION_DURATION/TIME_STEP; ++i) {
        incrementPendulums(p1, p2, TIME_STEP);
        positions.push_back(Eigen::Vector2d(p1.theta, p2.theta));
    }
    
    std::cout << "Length of positions: " << positions.size() << std::endl;
    
    sf::Clock deltaClock;
    double progress = 0;
    
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
        progress += dt.asSeconds() * DISPLAY_SPEEDUP;
        if (progress > SIMULATION_DURATION) {
            progress -= SIMULATION_DURATION;
        }
        
        //Figure out index to pull from
        int index = static_cast<int>(std::floor(progress/(SIMULATION_DURATION) * (SIMULATION_DURATION/(TIME_STEP))));
        
        double theta1 = positions[index](0);
        double theta2 = positions[index](1);
        
        //Draw the pendulums
        sf::RectangleShape rect1(sf::Vector2f(M_TO_PX*p1.width, M_TO_PX*p1.length));
        sf::RectangleShape rect2(sf::Vector2f(M_TO_PX*p2.width, M_TO_PX*p2.length));
        rect1.setOrigin(M_TO_PX*p1.width/2.0, M_TO_PX*p1.length);
        rect2.setOrigin(M_TO_PX*p2.width/2.0, M_TO_PX*p1.length);
        rect1.setPosition(X_OFFSET, Y_OFFSET);
        rect2.setPosition(X_OFFSET + M_TO_PX*p1.length*sin(theta1), Y_OFFSET + M_TO_PX*p1.length*cos(theta1));
        //std::cout << dt.asSeconds() << ":" << p1.theta << "," << p2.theta << std::endl;
        rect1.setRotation(translateRotation(theta1));
        rect2.setRotation(translateRotation(theta2));
        //std::cout << p1 << ", " << p2 << std::endl;
        rect1.setFillColor(sf::Color::Green);
        rect2.setFillColor(sf::Color::Blue);
        window.draw(rect1);
        window.draw(rect2);

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
