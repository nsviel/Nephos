#pragma once

#include <Utility/Specific/Common.h>

namespace vk{class Node;}
namespace eng{class Node;}
namespace scene{class Database;}
namespace scene{class Loader;}
namespace scene{class Exporter;}
namespace scene{class Format;}
namespace gly{class Node;}
namespace scene{class Operation;}
namespace scene{class Bookmark;}
namespace scene{class Entity;}
namespace scene{class Scene;}
namespace scene::gui{class Scene;}
namespace scene::gui{class Loader;}


namespace scene{

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

  inline scene::Format* get_scene_format(){return sce_format;}
  inline scene::Database* get_scene_database(){return sce_database;}
  inline scene::Loader* get_scene_loader(){return sce_loader;}
  inline scene::Exporter* get_scene_exporter(){return sce_exporter;}
  inline gly::Node* get_scene_glyph(){return node_glyph;}
  inline scene::Bookmark* get_scene_bookmark(){return sce_bookmark;}
  inline scene::Entity* get_scene_entity(){return sce_entity;}

private:
  //Dependancy
  eng::Node* node_engine;
  vk::Node* node_vulkan;

  //Child
  scene::Database* sce_database;
  gly::Node* node_glyph;
  scene::Loader* sce_loader;
  scene::Exporter* sce_exporter;
  scene::Format* sce_format;
  scene::Bookmark* sce_bookmark;
  scene::Scene* sce_scene;
  scene::gui::Scene* gui_scene;
  scene::gui::Loader* gui_loader;
  scene::Entity* sce_entity;

  bool show_scene = true;
  bool show_loader = true;
};

}
