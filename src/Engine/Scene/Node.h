#pragma once

#include <Utility/Specific/Common.h>

namespace vk{class Node;}
namespace eng{class Node;}
namespace sce{class Database;}
namespace ldr{class Loader;}
namespace ldr{class Exporter;}
namespace ldr{class Format;}
namespace gly{class Node;}
namespace sce{class Operation;}
namespace ldr{class Bookmark;}
namespace sce{class Entity;}
namespace sce{class Graph;}
namespace sce::gui{class Graph;}
namespace ldr::gui{class Loader;}


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

  inline ldr::Format* get_scene_format(){return sce_format;}
  inline sce::Database* get_scene_database(){return sce_database;}
  inline ldr::Loader* get_scene_loader(){return sce_loader;}
  inline ldr::Exporter* get_scene_exporter(){return sce_exporter;}
  inline gly::Node* get_scene_glyph(){return node_glyph;}
  inline ldr::Bookmark* get_scene_bookmark(){return sce_bookmark;}
  inline sce::Entity* get_scene_entity(){return sce_entity;}

private:
  //Dependancy
  eng::Node* node_engine;
  vk::Node* node_vulkan;

  //Child
  sce::Database* sce_database;
  gly::Node* node_glyph;
  ldr::Loader* sce_loader;
  ldr::Exporter* sce_exporter;
  ldr::Format* sce_format;
  ldr::Bookmark* sce_bookmark;
  sce::Graph* sce_graph;
  sce::gui::Graph* gui_scene;
  ldr::gui::Loader* gui_loader;
  sce::Entity* sce_entity;

  bool show_scene = true;
  bool show_loader = true;
};

}
