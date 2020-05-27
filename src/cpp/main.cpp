#include <iostream>
#include <random>

#include "system.hpp"
#include "flock.hpp"
#include "prey.hpp"
#include "predator.hpp"
#include "vec2.hpp"

#include "SFML/Window.hpp"

struct Options{
    int number_of_preys = 100;
    int number_of_predators = 3;
    bool abort = false;
    bool render = true;
    double window_height = -1;
    double window_width = -1;
    unsigned int iterations = 6000;
    bool random = false;
};

void parseOptions(Options&, int argc, char const **argv);

int main(int argc, char const *argv[]) {
    Options options;
    parseOptions(options, argc, argv);
    if(options.abort)
        return 0;

    System system(options.render, options.window_width, options.window_height);
    Flock flock(system.window_width, system.window_height);

    std::random_device rand_dev;
    std::mt19937 gen;
    if (options.random){
        gen = std::mt19937(rand_dev());
    } else {
      gen = std::mt19937(1);
    }
    std::uniform_real_distribution<double> dist_height(0.25*system.window_height, 0.75*system.window_height);
    std::uniform_real_distribution<double> dist_width(0.0, 0.5*system.window_width);
    std::uniform_real_distribution<double> dist_vel(0.8, 1);

    for (size_t i = 0; i < options.number_of_preys; i++) {
        Vec2 pos(dist_width(gen), dist_height(gen));
        Vec2 vel(rand()%3 - 1,  rand()%3 - 1);
        flock.addPrey(new Prey(pos, vel));
    }

    for(size_t i = 0; i < options.number_of_predators; i++){
        Vec2 pos(dist_width(gen), dist_height(gen));
        Vec2 vel(rand()%3 - 1,  rand()%3 - 1);
        flock.addPredator(new Predator(pos, vel));
    }

    // Create a system using this flock

    // Run the system for 10000 iterations
    std::cout << "Running simulation..." << std::endl;
    system.run(options.iterations, flock);
    std::cout << "Completed simulation." << std::endl;

    return 0;
}

class InputParser {
public:
  InputParser(int &argc, char const **argv) {
    for (int i = 1; i < argc; ++i)
      this->tokens.push_back(std::string(argv[i]));
  }
  /// @author iain
  const std::string &getCmdOption(const std::string &option) const {
    std::vector<std::string>::const_iterator itr;
    itr = std::find(this->tokens.begin(), this->tokens.end(), option);
    if (itr != this->tokens.end() && ++itr != this->tokens.end()) {
      return *itr;
    }
    static const std::string empty_string("");
    return empty_string;
  }
  /// @author iain
  bool cmdOptionExists(const std::string &option) const {
    return std::find(this->tokens.begin(), this->tokens.end(), option) !=
           this->tokens.end();
  }

private:
  std::vector<std::string> tokens;
};

void parseOptions(Options& options, int argc, char const **argv){
    InputParser input(argc, argv);
    if(input.cmdOptionExists("-h") || input.cmdOptionExists("--help")){
      std::cout << "Simulate flocking through natural selection\n\n"
                << "OPTIONS\n"
                << " --preys <num>        Number of prey boids.\n"
                << " --predators <num>    Number of predator boids.\n"
                << " -n, --norender       Do not render the simulation.\n"
                << " --width <width>      Set the width of the window.\n"
                << " --height <height>    Set the height of the window.\n"
                << " --random             Use random seed.\n"
                << " -h, --help           Show this message.\n\n"
                << "KEYMAP\n"
                << " esc, q               Quit the simulation.\n"
                << " a                    Draw acceleration vectors.\n"
                << " v                    Draw velocity vectors.\n"
                << " f                    Draw prey force vectors.\n"
                << " t                    Draw quad tree.\n"
                << std::endl;
      options.abort = true;
    }
    const std::string& numPreys = input.getCmdOption("--preys");
    if (!numPreys.empty()){
        options.number_of_preys = std::stoi(numPreys);
    }
    const std::string &numPredators = input.getCmdOption("--predators");
    if (!numPredators.empty()) {
      options.number_of_predators = std::stoi(numPredators);
    }
    if (input.cmdOptionExists("-n") || input.cmdOptionExists("--norender")) {
      options.render = false;
    }
    if (input.cmdOptionExists("--random")) {
        options.random = true;
    }
    const std::string &width = input.getCmdOption("--width");
    if (!width.empty()) {
        options.window_width = std::stod(width);
    }
    const std::string &height = input.getCmdOption("--height");
    if (!height.empty()) {
        options.window_height = std::stod(height);
    }
    const std::string &iterations = input.getCmdOption("--iterations");
    if (!iterations.empty()) {
      options.iterations = std::stoi(iterations);
    }
}
