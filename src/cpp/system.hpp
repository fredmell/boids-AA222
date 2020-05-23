#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "flock.hpp"

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

class System{
public:
    System(bool render);
    void run(unsigned int numIter, Flock &flock);
    void takeInput();
    void update(Flock &flock);
    void draw(Flock&);

    sf::RenderWindow window;
    int window_width;
    int window_height;
    bool do_render = true;
};

#endif // SYSTEM_HPP
