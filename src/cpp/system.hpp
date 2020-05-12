#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "flock.hpp"

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

class System{
public:
  System(bool show = true);
  void run(unsigned);
  void takeInput();
  void update();

private:
  sf::RenderWindow _window;
  int _window_width;
  int _window_height;
  Flock _flock;
  bool _show;

};

#endif // SYSTEM_HPP
