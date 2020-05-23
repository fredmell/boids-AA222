#include "flock.hpp"
#include "system.hpp"
#include "prey.hpp"
#include "predator.hpp"
#include "vec2.hpp"
#include "progress.hpp"

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"


System::System(bool render)
{
    do_render = render;
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    window_height = desktop.height;
    window_width = desktop.width;
    sf::VideoMode vidMode =
        sf::VideoMode(window_width, window_height, desktop.bitsPerPixel);

    if (render){
      window.create(vidMode, "Boids", sf::Style::None);
    }
}

void System::run(unsigned int numIter, Flock& flock){
    Progress progress(numIter);
    sf_velocities = sf::VertexArray(sf::Lines, 2*flock.boids.size());
    sf_accelerations = sf::VertexArray(sf::Lines, 2*flock.boids.size());

    for(unsigned int t=0; t<numIter; t++){
        if(do_render)
            takeInput();
        update(flock);

        // Handle the window
        if(do_render){
            draw(flock);
            if(not window.isOpen())
                break;
        }

        progress.step();
    }
    if(do_render)
        window.close();
}

void System::draw(Flock& flock){
    // Update window
    window.clear();
    flock.draw(window);
    if(do_render_vel)
        drawVelocities(flock);
    if(do_render_acc)
        drawAccelerations(flock);
    window.display();
}

void System::drawVelocities(Flock& flock){
    Boid* boid;
    sf::Vertex* line;
    Vec2 direction;
    for(size_t i = 0; i < flock.boids.size(); i++){
        boid = flock.boids[i];
        // [boid1.start, boid1.stop, boid2.start, boid2.stop, ...]
        line = &sf_velocities[2*i];
        direction = boid->pos + 20*boid->vel;
        line[0].position = sf::Vector2f(boid->pos.x, boid->pos.y);
        line[1].position = sf::Vector2f(direction.x, direction.y);
    }
    window.draw(sf_velocities);
}

void System::drawAccelerations(Flock& flock){
    Boid* boid;
    sf::Vertex* line;
    Vec2 direction;
    for(size_t i = 0; i < flock.boids.size(); i++){
        boid = flock.boids[i];
        // [boid1.start, boid1.stop, boid2.start, boid2.stop, ...]
        line = &sf_accelerations[2*i];
        direction = boid->pos + 200*boid->acc;
        line[0].position = sf::Vector2f(boid->pos.x, boid->pos.y);
        line[1].position = sf::Vector2f(direction.x, direction.y);
        line[0].color = sf::Color::Red;
        line[1].color = sf::Color::Red;
    }
    window.draw(sf_accelerations);
}


void System::update(Flock& flock){
    // Update positions/velocities
    flock.step(window_width, window_height);
}

void System::takeInput(){
    sf::Event event;
    while(window.pollEvent(event)){
        if( (event.type == sf::Event::Closed) ||
            (event.type == sf::Event::KeyPressed &&
             (event.key.code == sf::Keyboard::Escape) ||
             event.key.code == sf::Keyboard::Q) ){
                window.close();
        }
        else if(event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
            case sf::Keyboard::V : {
                do_render_vel = not do_render_vel;
                break;
            }
            case sf::Keyboard::A : {
                do_render_acc = not do_render_acc;
                break;
            }
            default:
                break;
            }
        }
    }
}
