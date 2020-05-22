#include "flock.hpp"
#include "system.hpp"
#include "prey.hpp"
#include "predator.hpp"
#include "vec2.hpp"

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

System::System(Flock& flock)
  : flock_(flock) {
  // sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
  // this->_window_height = desktop.height;
  // this->_window_width = desktop.width;
  this->_window_height = 1000;
  this->_window_width = 1000;
  sf::VideoMode vidMode = sf::VideoMode(this->_window_width,
                                        this->_window_height,
                                        desktop.bitsPerPixel);

  this->_window.create(vidMode, "Boids", sf::Style::None);
}

void System::run(unsigned int numIter){
  for(unsigned int t=0; t<numIter; t++){
    this->takeInput();
    this->update();
    if(not this->_window.isOpen()) break;
  }
}

void System::update(){
  // Update positions/velocities
  _flock.step(_window_width, _window_height);

  // Update window
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
