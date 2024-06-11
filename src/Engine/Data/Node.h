#pragma once

#include <Utility/Base/Type/Node.h>

namespace vk{class Node;}
namespace cam{class Node;}
namespace eng{class Node;}
namespace dat{class Graph;}
namespace dat{class Entity;}
namespace dat{class Set;}
namespace dat{class Image;}
namespace dat{class UID;}
namespace dat{class Glyph;}
namespace dat{class Selection;}
namespace dat{class Structure;}
namespace dat::gui{class Graph;}
namespace dat::gui{class Control;}
namespace dat::gui{class Wheel;}


namespace dat{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(eng::Node* node_engine);
  ~Node();

public:
  void init();
  void loop();
  void clean();
  void gui();
  void reset();

  inline eng::Node* get_node_engine(){return node_engine;}
  inline vk::Node* get_node_vulkan(){return node_vulkan;}
  inline cam::Node* get_node_camera(){return node_camera;}

  inline dat::Graph* get_dat_graph(){return dat_graph;}
  inline dat::Selection* get_dat_selection(){return dat_selection;}
  inline dat::Entity* get_dat_entity(){return dat_entity;}
  inline dat::Set* get_dat_set(){return dat_set;}
  inline dat::UID* get_dat_uid(){return dat_uid;}
  inline dat::Image* get_dat_image(){return dat_image;}
  inline dat::Glyph* get_dat_glyph(){return dat_glyph;}
  inline dat::Structure* get_dat_struct(){return dat_struct;}
  inline dat::gui::Control* get_gui_control(){return gui_control;}
  inline dat::gui::Wheel* get_gui_wheel(){return gui_wheel;}

private:
  //Dependancy
  eng::Node* node_engine;
  vk::Node* node_vulkan;
  cam::Node* node_camera;

  //Child
  dat::Structure* dat_struct;
  dat::Graph* dat_graph;
  dat::Entity* dat_entity;
  dat::Set* dat_set;
  dat::Glyph* dat_glyph;
  dat::UID* dat_uid;
  dat::Image* dat_image;
  dat::Selection* dat_selection;
  dat::gui::Graph* gui_graph;
  dat::gui::Control* gui_control;
  dat::gui::Wheel* gui_wheel;

  bool show_scene = true;
  bool show_loader = true;
};

}
