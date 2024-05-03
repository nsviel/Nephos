#pragma once

#include <Utility/Base/Type/Node.h>

namespace vk{class Node;}
namespace eng{class Node;}
namespace dat{class Graph;}
namespace dat{class Entity;}
namespace dat{class Set;}
namespace dat{class Glyph;}
namespace dat{class Structure;}
namespace dat::gui{class Graph;}


namespace dat{

class Node : public utl::type::Node
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

  inline dat::Graph* get_data_graph(){return dat_graph;}
  inline dat::Entity* get_data_entity(){return dat_entity;}
  inline dat::Set* get_data_set(){return dat_set;}
  inline dat::Glyph* get_data_glyph(){return dat_glyph;}
  inline dat::Structure* get_data_struct(){return dat_struct;}

private:
  //Dependancy
  eng::Node* node_engine;
  vk::Node* node_vulkan;

  //Child
  dat::Structure* dat_struct;
  dat::Graph* dat_graph;
  dat::Entity* dat_entity;
  dat::Glyph* dat_glyph;
  dat::Set* dat_set;
  dat::gui::Graph* gui_graph;

  bool show_scene = true;
  bool show_loader = true;
};

}
