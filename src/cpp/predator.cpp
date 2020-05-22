#include "predator.hpp"
#include "boid.hpp"

#include "SFML/Graphics.hpp"

Predator::Predator(Vec2 x0, Vec2 v0) : Boid(x0, v0) {
    shape.setFillColor(sf::Color::Red);
}

void Predator::computeForce(std::vector<Prey*>& preys, std::vector<Predator*>& predators){

}
