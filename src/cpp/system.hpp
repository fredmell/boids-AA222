#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "flock.hpp"

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

class System{
public:
  System(Flock&);
  void run(unsigned int numIter);
  void takeInput();
  void update();

  sf::RenderWindow window;
  int window_width;
  int window_height;
  Flock flock;

};

#endif // SYSTEM_HPP
