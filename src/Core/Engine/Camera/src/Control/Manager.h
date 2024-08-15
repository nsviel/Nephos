#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace dat::gph{class Graph;}
namespace dat::elm{class Glyph;}
namespace dat::elm{class Set;}
namespace core{class Node;}
namespace cam{class Node;}
namespace cam{class Entity;}
namespace cam{class Structure;}
namespace cam{class Control;}
namespace vk::image{class Screenshot;}


namespace cam{

class Manager
{
public:
  Manager(cam::Node* node_camera);
  ~Manager();

public:
  //Main function
  void create_camera();
  void reset_camera();
  void make_screenshot();

private:
  core::Node* node_core;
  cam::Structure* cam_struct;
  cam::Control* cam_control;
  vk::image::Screenshot* vk_screenshot;
  dat::gph::Graph* dat_graph;
  dat::elm::Glyph* dat_glyph;
  dat::elm::Set* dat_set;
};

}
