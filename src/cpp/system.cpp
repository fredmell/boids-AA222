#include "flock.hpp"
#include "system.hpp"
#include "boid.hpp"
#include "vec2.hpp"

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

System::System(bool show){
  _show = show;
  if(show){
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
    _flock.addBoid(boid);
  }
  Vec2 pos(_window_width / 3, _window_height / 3);
  Vec2 vel(1.0, 0.0);
  _flock.addBoid(Boid(pos, vel, true));

  // Game loop
  while(_window.isOpen()){
    if(_show) takeInput();
    update();
  }
}

void System::update(){
  _flock.step(_window_width, _window_height);
  if(_show){
    _window.clear();
    _flock.draw(_window);
    _window.display();
  }
}

void System::takeInput(){
  sf::Event event;
  while(_window.pollEvent(event)){
    if( (event.type == sf::Event::Closed) ||
        (event.type == sf::Event::KeyPressed &&
         event.key.code == sf::Keyboard::Escape) ){
      _window.close();};
  }
}
