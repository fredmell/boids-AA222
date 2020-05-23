#ifndef PROGRESS_H
#define PROGRESS_H

#include <iostream>

class Progress {
public:
  Progress(int max) : stop(max), step_size((double)max / width) {
    draw();
    next = step_size;
  }
  void step() {
    current++;
    if (current >= next)
      draw();
  }

  void draw() {
    double progress = (double)current / stop;
    int pos = width * progress;
    std::cout << "[";
    for (int i = 0; i < width; i++) {
      if (i < pos)
        std::cout << "=";
      else if (i == pos)
        std::cout << ">";
      else
        std::cout << " ";
    }
    std::cout << "] " << int(100 * progress) << " %\r" << std::flush;
    next += step_size;
    if (next >= stop)
      next = stop;
    if (current == stop)
      std::cout << std::endl;
  }

  int current = 0;
  int next = 0;
  const double step_size;
  const int stop;
  const int width = 70;
};

#endif /* PROGRESS_H */
