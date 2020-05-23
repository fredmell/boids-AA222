#include "prey.hpp"
#include "boid.hpp"
#include "predator.hpp"

#include "SFML/Graphics.hpp"

Prey::Prey(Vec2 x0, Vec2 v0) : Boid(x0, v0) {
    color = sf::Color::Green;
    //shape.setFillColor(sf::Color::Green);
}

void Prey::computeForce(std::vector<Prey*>& preys, std::vector<Predator*>& predators){

}
