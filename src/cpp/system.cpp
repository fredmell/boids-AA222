#include "flock.hpp"
#include "system.hpp"
#include "boid.hpp"
#include "vec2.hpp"

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

System::System(bool show){
  _show = show;
  if(show){
    _boidSize = 3.0;

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    this->_window_height = desktop.height;
    this->_window_width = desktop.width;
    sf::VideoMode vidMode = sf::VideoMode(this->_window_width,
                                          this->_window_height,
                                          desktop.bitsPerPixel);

    this->_window.create(vidMode, "Boids", sf::Style::None);
  }
}

void System::run(unsigned int numBoids){
  for(unsigned int i=0; i<numBoids; i++){
    Vec2 pos(_window_width / 3 + 50*i, _window_height/3);
    Vec2 vel(0.0, 1.0);
    Boid boid(pos, vel);
    sf::CircleShape shape(8,3);

    shape.setPosition(_window_width, _window_height);
    shape.setOutlineColor(sf::Color(0,255,0));
    shape.setFillColor(sf::Color::Green);
    shape.setOutlineThickness(1);
    shape.setRadius(_boidSize);

    _flock.addBoid(boid);
    _shapes.push_back(shape);
  }

  // Game loop
  while(_window.isOpen()){
    if(_show) takeInput();
    update();
  }
}

void System::takeInput(){
  sf::Event event;
  while(_window.pollEvent(event)){
    if(event.type == sf::Event::Closed) _window.close();
  }
}

void System::update(){
  _flock.step(_window_width, _window_height);
  if(_show){
    _window.clear();

    for (unsigned i=0; i<_flock.size(); i++){
      _window.draw(_shapes.at(i));

      Boid b = _flock.getBoid(i);
      _shapes.at(i).setPosition(b.pos().x, b.pos().y);

      double theta = b.directionAngle();
      _shapes.at(i).setRotation(theta);
    }
  _window.display();
  }
}
