#pragma once

#include <Utility/Specific/Common.h>

namespace vk{class Node;}
namespace eng{class Node;}
namespace dat{class Database;}
namespace gly{class Node;}
namespace sce{class Operation;}
namespace dat{class Entity;}
namespace sce{class Graph;}
namespace sce::gui{class Graph;}
namespace eng::module{class Node;}


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

  inline dat::Database* get_database(){return dat_database;}
  inline dat::Entity* get_entity(){return dat_entity;}

private:
  //Dependancy
  eng::Node* node_engine;
  vk::Node* node_vulkan;

  //Child
  dat::Database* dat_database;
  gly::Node* node_glyph;
  sce::Graph* sce_graph;
  sce::gui::Graph* gui_graph;
  dat::Entity* dat_entity;
  eng::module::Node* node_module;

  bool show_scene = true;
  bool show_loader = true;
};

}
