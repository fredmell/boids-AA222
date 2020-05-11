#include <iostream>

#include "vec2.hpp"
#include "boid.hpp"
#include "flock.hpp"
#include "system.hpp"

#include "SFML/Window.hpp"

int main(int argc, char const *argv[]) {

  // Create a system with visualization
  System system(true);

  // Run system with one boid
  system.run(10);

  return 0;
}
