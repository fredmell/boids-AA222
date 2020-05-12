#ifndef FLOCK_HPP
#define FLOCK_HPP

#include <vector>

#include "boid.hpp"

#include "SFML/Window.hpp"

class Flock{
public:
  std::size_t size(){
    return _flock.size();
  }

  void addBoid(Boid boid){
    _flock.push_back(boid);
  };

  Boid getBoid(unsigned int i){
    return _flock.at(i);
  }

  void step(int width, int height){
    // Loop through all Boids, step and wrap positions
    for(unsigned i=0; i<size(); i++){
      bool alive = true;
      _flock.at(i).step(_flock, alive);
      // Remove dead boids
      _deceased.push_back(_flock.at(i));
      if (not alive) _flock.erase(_flock.begin()+i);

      _flock.at(i).wrap(width, height);
    }
  }

  void draw(sf::RenderWindow& window){
    for (unsigned i=0; i<_flock.size(); i++){
      _flock.at(i).draw(window);
    }
  }

private:
  std::vector<Boid> _flock;
  std::vector<Boid> _deceased;
};

#endif // FLOCK_HPP
