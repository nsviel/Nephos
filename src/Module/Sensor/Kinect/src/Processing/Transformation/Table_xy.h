#pragma once

#include <Dynamic/src/Thread/Task.h>

namespace k4n{class Node;}
namespace k4n{class Structure;}
namespace k4n::base{class Sensor;}

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


namespace k4n::processing::image{

class Table_xy : public dyn::thread::Task
{
public:
  //Constructor / Destructor
  Table_xy(k4n::Node* node_k4n);
  ~Table_xy();

public:
  //Main function
  void thread_function();

  //Subfunction
  void table_color_to_depth(k4n::base::Sensor* sensor, cmap& map_xy);
  void convert_table_to_glm(k4n::base::Sensor* sensor, cmap& map_xy);

private:
  k4n::Structure* k4n_struct;
};

}
