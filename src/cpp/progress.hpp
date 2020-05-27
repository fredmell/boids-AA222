#ifndef PROGRESS_H
#define PROGRESS_H

#include <iostream>

class Progress {
public:
    Progress(int max) : stop(max),
                        width(70){
        step_size = max/((double)width);
        next = step_size;
        draw();
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
  double step_size;
  const int stop;
  const int width;
};

#endif /* PROGRESS_H */
