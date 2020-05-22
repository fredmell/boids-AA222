#include "flock.hpp"
#include "system.hpp"
#include "prey.hpp"
#include "predator.hpp"
#include "vec2.hpp"

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

System::System(Flock& f)
    : flock(f) {
        sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
        window_height = desktop.height;
        window_width = desktop.width;
        sf::VideoMode vidMode = sf::VideoMode(window_width,
                                              window_height,
                                              desktop.bitsPerPixel);

        window.create(vidMode, "Boids", sf::Style::None);
}

void System::run(unsigned int numIter){
    for(unsigned int t=0; t<numIter; t++){
        this->takeInput();
        this->update();
        if(not window.isOpen()) break;
    }
}

void System::update(){
    // Update positions/velocities
    flock.step(window_width, window_height);

    // Update window
    window.clear();
    flock.draw(window);
    window.display();
}

void System::takeInput(){
    sf::Event event;
    while(window.pollEvent(event)){
        if( (event.type == sf::Event::Closed) ||
            (event.type == sf::Event::KeyPressed &&
             event.key.code == sf::Keyboard::Escape) ){
                window.close();
        }
    }
}
