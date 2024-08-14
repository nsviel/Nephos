#pragma once

#include <Utility/Base/Class/Node.h>

namespace vk{class Node;}
namespace eng{class Node;}
namespace dat::element{class Entity;}
namespace dat::element{class Set;}
namespace dat::element{class Image;}
namespace dat{class Glyph;}
namespace dat{class Structure;}
namespace dat::graph{class Node;}


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

  inline dat::element::Entity* get_dat_entity(){return dat_entity;}
  inline dat::element::Set* get_dat_set(){return dat_set;}
  inline dat::element::Image* get_dat_image(){return dat_image;}
  inline dat::Glyph* get_dat_glyph(){return dat_glyph;}
  inline dat::Structure* get_dat_struct(){return dat_struct;}
  inline dat::graph::Node* get_node_graph(){return node_graph;}

private:
  //Dependancy
  eng::Node* node_engine;
  vk::Node* node_vulkan;
  dat::graph::Node* node_graph;

  //Child
  dat::Structure* dat_struct;
  dat::element::Entity* dat_entity;
  dat::element::Set* dat_set;
  dat::Glyph* dat_glyph;
  dat::element::Image* dat_image;

  bool show_scene = true;
  bool show_loader = true;
};

}