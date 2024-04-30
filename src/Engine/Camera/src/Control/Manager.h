#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace dat{class Glyph;}
namespace dat{class Graph;}
namespace dat{class Set;}
namespace cam{class Node;}
namespace cam{class Entity;}


namespace cam{

class Manager
{
public:
  Manager(cam::Node* node_camera);
  ~Manager();

public:
  //Main function
  void create_camera();
  void reset();

  inline cam::Entity* get_camera(int i){return vec_camera[i];}
  inline cam::Entity* get_current_camera(){return current_camera;}

private:
  dat::Glyph* dat_glyph;
  dat::Graph* dat_graph;
  dat::Set* dat_set;

  std::vector<cam::Entity*> vec_camera;
  cam::Entity* current_camera;
  int camera_ID;
};

}
