#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace dat{class Graph;}
namespace dat{class Glyph;}
namespace dat::element{class Set;}
namespace eng{class Node;}
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
  eng::Node* node_engine;
  cam::Structure* cam_struct;
  cam::Control* cam_control;
  vk::image::Screenshot* vk_screenshot;
  dat::Graph* dat_graph;
  dat::Glyph* dat_glyph;
  dat::element::Set* dat_set;
};

}
