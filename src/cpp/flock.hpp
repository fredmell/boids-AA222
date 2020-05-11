#ifndef FLOCK_HPP
#define FLOCK_HPP

#include <vector>
#include "boid.hpp"

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
    for(unsigned i=0; i<size(); i++){
      _flock.at(i).wrap(width, height);
      _flock.at(i).step();
    }
  }

private:
  std::vector<Boid> _flock;
};

#endif // FLOCK_HPP
