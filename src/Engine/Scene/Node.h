#pragma once

#include <Utility/Specific/Common.h>

namespace vk{class Node;}
namespace eng{class Node;}
namespace dat{class Database;}
namespace ldr{class Loader;}
namespace ldr{class Exporter;}
namespace ldr{class Format;}
namespace gly{class Node;}
namespace sce{class Operation;}
namespace ldr{class Bookmark;}
namespace dat{class Entity;}
namespace sce{class Graph;}
namespace sce::gui{class Graph;}
namespace ldr::gui{class Loader;}
namespace eng::module{class Node;}


namespace sce{

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

  inline ldr::Format* get_scene_format(){return ldr_format;}
  inline dat::Database* get_scene_database(){return dat_database;}
  inline ldr::Loader* get_scene_loader(){return ldr_loader;}
  inline ldr::Exporter* get_scene_exporter(){return ldr_exporter;}
  inline gly::Node* get_scene_glyph(){return node_glyph;}
  inline ldr::Bookmark* get_scene_bookmark(){return ldr_bookmark;}
  inline dat::Entity* get_scene_entity(){return dat_entity;}

private:
  //Dependancy
  eng::Node* node_engine;
  vk::Node* node_vulkan;

  //Child
  dat::Database* dat_database;
  gly::Node* node_glyph;
  ldr::Loader* ldr_loader;
  ldr::Exporter* ldr_exporter;
  ldr::Format* ldr_format;
  ldr::Bookmark* ldr_bookmark;
  sce::Graph* sce_graph;
  sce::gui::Graph* gui_scene;
  ldr::gui::Loader* gui_loader;
  dat::Entity* dat_entity;
  eng::module::Node* node_module;

  bool show_scene = true;
  bool show_loader = true;
};

}
