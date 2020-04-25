#include <iostream>

#include "vec2.hpp"

int main(int argc, char const *argv[]) {
  Vec2 vec(2, 3.2);
  Vec2 vec2(2, 1);
  (vec + vec2).print();
  return 0;
}
