#pragma once

#include <Kinect/src/Structure/Data/Data.h>
#include <k4a/k4a.hpp>
#include <glm/glm.hpp>
#include <unordered_map>
#include <vector>


namespace k4n::transformation{

struct Vec2Hash {
  std::size_t operator()(const glm::ivec2& vec) const {
    // Combine hash of x and y using a simple hash function
    return std::hash<int>()(vec.x) ^ (std::hash<int>()(vec.y) << 1);
  }
};
struct Vec2Equal {
  bool operator()(const glm::ivec2& a, const glm::ivec2& b) const {
    return a.x == b.x && a.y == b.y;
  }
};
typedef std::unordered_map<glm::ivec2, glm::ivec2, Vec2Hash, Vec2Equal> cmap;

enum Mode{
  DEPTH_TO_COLOR = 0,
  COLOR_TO_DEPTH = 1,
};

struct Structure{
  //---------------------------

  int mode = k4n::transformation::COLOR_TO_DEPTH;

  //Color to depth coordinate mapping
  std::vector<glm::ivec4> table_xy;
  k4n::transformation::cmap mapping;

  //---------------------------
};

}
