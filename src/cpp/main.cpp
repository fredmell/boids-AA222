#include <iostream>
#include <random>
#include <algorithm>
#include <cassert>

#include "system.hpp"
#include "flock.hpp"
#include "prey.hpp"
#include "predator.hpp"
#include "vec2.hpp"

#include "SFML/Window.hpp"

struct Options{
    int num_generations = 500;
    int number_of_preys = 200;
    int number_of_predators = 10;
    bool abort = false;
    bool render = false;
    double window_height = -1;
    double window_width = -1;
    unsigned int iterations = 8000;
    bool random = false;
};

struct Params{
    double separation = 1.0;
    double alignment = 1.5;
    double cohesion = 1.0;
};

void parseOptions(Options&, int argc, char const **argv);

int main(int argc, char const *argv[]) {
    Options options;
    parseOptions(options, argc, argv);
    if(options.abort)
        return 0;

    System system(options.render, options.window_width, options.window_height);

    std::random_device rand_dev;
    std::mt19937 gen;
    if (options.random){
        gen = std::mt19937(rand_dev());
    } else {
      gen = std::mt19937(1);
    }
    std::uniform_real_distribution<double> dist_height(0.2*system.window_height, 0.8*system.window_height);
    std::uniform_real_distribution<double> dist_width(0.2*system.window_width, 0.8*system.window_width);

    std::uniform_real_distribution<double> dist_separation(0.0, 4.0);
    std::uniform_real_distribution<double> dist_alignment(0.0, 2.0);
    std::uniform_real_distribution<double> dist_cohesion(0.0, 2.0);

    // Initialize the boid parameters
    std::vector<Params> design;
    for(size_t i=0; i < options.number_of_preys; i++){
        Params params;
        params.separation = dist_separation(gen);
        params.alignment = dist_alignment(gen);
        params.cohesion = dist_cohesion(gen);
        design.push_back(params);
    }

    // Run all generations of evolution
    std::vector<double> survivor_counts;
    for(int generation=0; generation<options.num_generations; generation++){
        // Set up the flock
        System system(options.render, options.window_width, options.window_height);

        Flock flock(system.window_width, system.window_height);
        for (size_t i = 0; i < options.number_of_preys; i++) {
            Vec2 pos(dist_width(gen), dist_height(gen));
            Vec2 vel(rand()%3 - 1,  rand()%3 - 1);
            Prey* prey = new Prey(
                pos,
                vel,
                design.at(i).separation,
                design.at(i).alignment,
                design.at(i).cohesion
            );
            flock.addPrey(prey);
        }

        for(size_t i = 0; i < options.number_of_predators; i++){
            Vec2 pos(dist_width(gen), dist_height(gen));
            Vec2 vel(rand()%3 - 1,  rand()%3 - 1);
            flock.addPredator(new Predator(pos, vel));
        }

        // Run the system
        system.run(options.iterations, flock, false);

        int lag = std::min(10, generation+1);
        double num_survivors = (double)flock.preys.size()
                             / (double)options.number_of_preys;
        survivor_counts.push_back(num_survivors);
        double sum_survivors = std::accumulate(survivor_counts.end()-lag,
                                               survivor_counts.end(),
                                               0.0);
        double avg_survivors = sum_survivors/( (double)lag );

        std::cout << "Generation: "     << generation << " - "
                  << "Survivors: "      << num_survivors << " - "
                  << "Avg. survivors: " << avg_survivors << std::endl;

        if(generation % 10 == 0){
            // Print statistics
            double avg_sep = 0.0, avg_align = 0.0, avg_cohesion = 0.0;
            double sd_sep  = 0.0, sd_align = 0.0, sd_cohesion = 0.0;
            for(Params params : design){
                avg_sep += params.separation;
                avg_align += params.alignment;
                avg_cohesion += params.cohesion;
            }

            avg_sep /= (double)design.size();
            avg_align /= (double)design.size();
            avg_cohesion /= (double)design.size();

            for(Params params : design){
                sd_sep += (params.separation - avg_sep)*(params.separation - avg_sep);
                sd_align += (params.alignment - avg_align)*(params.alignment - avg_align);
                sd_cohesion += (params.cohesion - avg_cohesion)*(params.cohesion - avg_cohesion);
            }

            sd_sep /= (double)design.size() - 1;
            sd_align /= (double)design.size() - 1;
            sd_cohesion /= (double)design.size() - 1;

            sd_sep = std::sqrt(sd_sep);
            sd_align = std::sqrt(sd_align);
            sd_cohesion = std::sqrt(sd_cohesion);

            std::cout << "Separation - Avg: " << avg_sep << " - Sd: " << sd_sep << std::endl;
            std::cout << "Alignment - Avg: " << avg_align << " - Sd: " << sd_align << std::endl;
            std::cout << "Cohesion - Avg: " << avg_cohesion << " - Sd: " << sd_cohesion << std::endl;
        }

        // Retrieve params of survivors.
        std::vector<Params> survivors;
        for( Prey* prey : flock.preys ){
            Params params;
            params.separation = prey->separation_coeff;
            params.alignment = prey->alignment_coeff;
            params.cohesion = prey->cohesion_coeff;
            survivors.push_back(params);
        }
        assert(survivors.size() == flock.preys.size());

        // Combine these to form new boids
        design.clear();
        std::uniform_int_distribution<int> idx(0,survivors.size()-1);
        std::normal_distribution<double> normal(0, 0.1);
        while(design.size() != options.number_of_preys){
            // Sample two parents
            Params parent1 = survivors.at(idx(gen));
            Params parent2 = survivors.at(idx(gen));

            // Combine the genes of these to form a child with sampling parents params
            Params child = parent1;
            if(rand()%2 == 0) child.separation = parent2.separation;
            if(rand()%2 == 0) child.alignment = parent2.alignment;
            if(rand()%2 == 0) child.cohesion = parent2.cohesion;

            // With some probability, mutate
            if(rand()%10 == 0) child.separation += normal(gen);
            if(rand()%10 == 0) child.alignment += normal(gen);
            if(rand()%10 == 0) child.cohesion += normal(gen);

            design.push_back(child);
        }

        survivors.clear();

        assert(design.size() == options.number_of_preys);
    }

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
                << " --gen <num>          Number of generations of evolution.\n"
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
    const std::string& numGen = input.getCmdOption("--gen");
    if (!numGen.empty()){
        options.num_generations = std::stoi(numGen);
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
