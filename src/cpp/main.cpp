#include <iostream>
#include <stdlib.h>

#include "system.hpp"
#include "flock.hpp"
#include "prey.hpp"
#include "predator.hpp"
#include "vec2.hpp"

#include "SFML/Window.hpp"

struct Options{
    int number_of_preys = 10;
    int number_of_predators = 3;
    bool abort = false;
};

void parseOptions(Options&, int argc, char const **argv);

int main(int argc, char const *argv[]) {
    srand(time(NULL));

    Options options;
    parseOptions(options, argc, argv);
    if(options.abort)
        return 0;
    // Create flock
    Flock flock;

    for(size_t i = 0; i < options.number_of_preys; i++){
        Vec2 pos(rand()%1000, rand()%1000);
        Vec2 vel(rand()%2, rand()%2);
        flock.addPrey(new Prey(pos, vel));
    }

    for(size_t i = 0; i < options.number_of_predators; i++){
      Vec2 pos(rand() % 1000, rand() % 1000);
      Vec2 vel(rand() % 2, rand() % 2);
      flock.addPredator(new Predator(pos + Vec2(0.0, 100.0), vel));
    }

    // Create a system using this flock
    System system;

    // Run the system for 10000 iterations
    system.run(10000, flock);

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
                  << "--preys     <number of prey boids>\n"
                  << "--predators <number of predator boids>\n";
        options.abort = true;
    }
    const std::string& numPreys = input.getCmdOption("--preys");
    if (!numPreys.empty()){
        options.number_of_preys = std::stoi(numPreys);
    }
    const std::string &numPredators = input.getCmdOption("--predators");
    if (!numPreys.empty()) {
      options.number_of_predators = std::stoi(numPredators);
    }
}
