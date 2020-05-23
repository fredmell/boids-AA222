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
    window.display();
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
             event.key.code == sf::Keyboard::Escape) ){
                window.close();
        }
    }
}
