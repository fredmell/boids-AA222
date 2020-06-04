#include <chrono>
#include <sstream>
#include <iomanip>

#include "flock.hpp"
#include "system.hpp"
#include "prey.hpp"
#include "predator.hpp"
#include "vec2.hpp"
#include "progress.hpp"

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

std::string beautifyDuration(std::chrono::microseconds input_seconds);

System::System(bool render, double width, double height)
{
    do_render = render;
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    window_height = (height <= 0) ? desktop.height : height;
    window_width  = (width <= 0)  ? desktop.width  : width;
    sf::VideoMode vidMode =
        sf::VideoMode(window_width, window_height, desktop.bitsPerPixel);

    if (render){
      window.create(vidMode, "Boids", sf::Style::None);
      view = sf::View(sf::FloatRect(0, 0, window_width, window_height));
      window.setView(view);
    }
}

System::~System(){
    window.close();
}

void System::run(unsigned int numIter, Flock& flock, bool verbose){
    Progress progress(numIter);
    if(do_render){
        sf_boids = sf::VertexArray(sf::Triangles, 3*flock.boids.size());
        sf_velocities = sf::VertexArray(sf::Lines, 2*flock.boids.size());
        sf_accelerations = sf::VertexArray(sf::Lines, 2*flock.boids.size());
        sf_forces = sf::VertexArray(sf::Lines, 4*2*flock.boids.size());
    }

    auto start = std::chrono::high_resolution_clock::now();
    if(verbose) std::cout << "Running simulation..." << std::endl;

    for(unsigned int t=0; t<numIter; t++){
        if(do_render)
            takeInput();
        update(flock, t);

        // Handle the window
        if(do_render){
            draw(flock);
            if(not window.isOpen())
                break;
        }

        progress.step();
    }

    if(verbose){
        std::cout << "Completed simulation." << std::endl;
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start);
        std::cout << "\nElapsed time: " << beautifyDuration(duration) << std::endl;
    }

    if(do_render)
        window.close();
}

void System::draw(Flock& flock){
    // Update window
    window.clear();

    // Update arrays to take account for dead boids
    if (3*flock.boids.size() != sf_boids.getVertexCount()){
        sf_boids.resize(3*flock.boids.size());
        sf_velocities.resize(2 * flock.boids.size());
        sf_accelerations.resize(2 * flock.boids.size());
        sf_forces.resize(4 * 2 * flock.preys.size());
    }

    // Want a single iteration through the boids
    Boid* boid;
    sf::Vertex* vertex;
    Vec2 direction;
    for(size_t i = 0; i < flock.boids.size(); i++){
        boid = flock.boids[i];
        vertex = &sf_boids[3*i];
        boid->makeTriangle(vertex);

        // Draw velocities
        if (do_render_vel){
            vertex = &sf_velocities[2*i];
            boid->drawVelocity(vertex);
        }
        // Draw acceleration
        if (do_render_acc){
            vertex = &sf_accelerations[2*i];
            boid->drawAcceleration(vertex);
        }
    }
    window.draw(sf_boids);

    if(do_render_forces){
        Prey *prey;
        for (size_t i = 0; i < flock.preys.size(); i++) {
            prey = flock.preys[i];
            vertex = &sf_forces[4 * 2 * i];
            prey->drawForces(vertex);
        }
        window.draw(sf_forces);
    }
    if (do_render_qtree){
        //std::cout << "SIZE: " << flock.qtree->getDepth() << std::endl;
        //std::cout << "SZIE: " << 8*(flock.qtree->getDepth()) << std::endl;
        sf::VertexArray sf_qtree(sf::Lines, 8*(flock.qtree->getDepth()));
        flock.qtree->draw(sf_qtree);
        window.draw(sf_qtree);
    }

    if (do_render_vel)
        window.draw(sf_velocities);
    if (do_render_acc)
        window.draw(sf_accelerations);

    window.display();
}

void System::update(Flock& flock, unsigned t){
    // Update positions/velocities
    flock.step(window_width, window_height, t);
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
            case sf::Keyboard::F: {
              do_render_forces = not do_render_forces;
              break;
            }
            case sf::Keyboard::T: {
                do_render_qtree = not do_render_qtree;
                break;
            }
            case sf::Keyboard::Z : {
                view.zoom(0.5f);
                window.setView(view);
                break;
            }
            default:
                break;
            }
        } else if (event.type == sf::Event::Resized) {
            // update the view to the new size of the window
            sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
            window.setView(sf::View(visibleArea));
        } else if (event.type == sf::Event::MouseWheelScrolled) {
            int delta = event.mouseWheelScroll.delta;
            if (delta < 0){
                view.zoom(0.9f);
            } else {
                view.zoom(1.1f);
            }
            window.setView(view);
        }
    }
}

std::string beautifyDuration(std::chrono::microseconds input_seconds)
{
    using namespace std::chrono;
    typedef duration<int, std::ratio<86400>> days;
    auto d = duration_cast<days>(input_seconds);
    input_seconds -= d;
    auto h = duration_cast<hours>(input_seconds);
    input_seconds -= h;
    auto m = duration_cast<minutes>(input_seconds);
    input_seconds -= m;
    auto s = duration_cast<seconds>(input_seconds);
    input_seconds -= s;
    auto ms = duration_cast<milliseconds>(input_seconds);
    input_seconds -= ms;

    auto dc = d.count();
    auto hc = h.count();
    auto mc = m.count();
    auto sc = s.count();
    auto msc = ms.count();

    std::stringstream ss;
    ss.fill('0');
    if (dc) {
        ss << dc << "d ";
    }
    if (dc || hc) {
        if (dc) { ss << std::setw(2); } //pad if second set of numbers
        ss << hc << "h ";
    }
    if (dc || hc || mc) {
        if (dc || hc) { ss << std::setw(2); }
        ss << mc << "m ";
    }
    if (dc || hc || mc || sc) {
        if (dc || hc || mc) { ss << std::setw(2); }
        ss << sc << "s ";
    }
    if (dc || hc || mc || sc || msc) {
      if (dc || hc || mc || sc) {
        ss << std::setw(2);
      }
      ss << msc << "ms ";
    }

    return ss.str();
}
