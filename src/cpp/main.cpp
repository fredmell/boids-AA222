#include <iostream>

#include "system.hpp"
#include "flock.hpp"
#include "prey.hpp"
#include "predator.hpp"
#include "vec2.hpp"

#include "SFML/Window.hpp"

int main(int argc, char const *argv[]) {

    // Create flock
    Flock flock;

    for(unsigned i=0; i<30; i++){
        Vec2 pos(100 + static_cast<double>(i*10), 100);
        Vec2 vel(0.0, 2.0);
        flock.addPrey(new Prey(pos, vel));
        flock.addPredator(new Predator(pos + Vec2(0.0, 100.0), vel));
    }

    // Create a system using this flock
    System system;

    // Run the system for 10000 iterations
    system.run(10000, flock);

    return 0;
}
