#pragma once

#include <Utility/Base/Class/Node.h>

namespace vk{class Node;}
namespace eng{class Node;}
namespace dat{class Graph;}
namespace dat::element{class Entity;}
namespace dat::element{class Set;}
namespace dat::element{class Image;}
namespace dat::graph{class UID;}
namespace dat{class Glyph;}
namespace dat::graph{class Selection;}
namespace dat{class Structure;}
namespace dat::gui{class Graph;}


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

  inline dat::Graph* get_dat_graph(){return dat_graph;}
  inline dat::graph::Selection* get_dat_selection(){return dat_selection;}
  inline dat::element::Entity* get_dat_entity(){return dat_entity;}
  inline dat::element::Set* get_dat_set(){return dat_set;}
  inline dat::graph::UID* get_dat_uid(){return dat_uid;}
  inline dat::element::Image* get_dat_image(){return dat_image;}
  inline dat::Glyph* get_dat_glyph(){return dat_glyph;}
  inline dat::Structure* get_dat_struct(){return dat_struct;}

private:
  //Dependancy
  eng::Node* node_engine;
  vk::Node* node_vulkan;

  //Child
  dat::Structure* dat_struct;
  dat::Graph* dat_graph;
  dat::element::Entity* dat_entity;
  dat::element::Set* dat_set;
  dat::Glyph* dat_glyph;
  dat::graph::UID* dat_uid;
  dat::element::Image* dat_image;
  dat::graph::Selection* dat_selection;
  dat::gui::Graph* gui_graph;

  bool show_scene = true;
  bool show_loader = true;
};

}
