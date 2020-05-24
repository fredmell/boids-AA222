#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "flock.hpp"

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

class System{
public:
    System(bool render, double width, double height);
    void run(unsigned int numIter, Flock &flock);
    void takeInput();
    void update(Flock &flock);
    void draw(Flock&);

    sf::RenderWindow window;
    sf::View view;
    sf::VertexArray sf_boids;
    sf::VertexArray sf_velocities;
    sf::VertexArray sf_accelerations;
    int window_width;
    int window_height;
    bool do_render = true;
    bool do_render_vel = false;
    bool do_render_acc = false;
};

#endif // SYSTEM_HPP
