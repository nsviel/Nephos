#pragma once

#include <Utility/Specific/common.h>

namespace vk{class Node;}
namespace eng{class Node;}
namespace eng::scene{class Parameter;}
namespace eng::scene{class Database;}
namespace eng::scene{class Loader;}
namespace eng::scene{class Format;}
namespace eng::scene{class Glyph;}
namespace eng::scene{class Operation;}
namespace eng::scene{class Bookmark;}
namespace eng::scene{class Entity;}
namespace eng::scene::gui{class Scene;}
namespace eng::scene::gui{class Loader;}


namespace eng::scene{

class Node : public utl::type::Node
{
public:
  //Constructor / Destructor
  Node(eng::Node* node_engine);
  ~Node();

public:
  void init();
  void loop();
  void gui();
  void reset();

  inline eng::Node* get_node_engine(){return node_engine;}
  inline vk::Node* get_node_vulkan(){return node_vulkan;}

  inline eng::scene::Parameter* get_scene_param(){return sce_param;}
  inline eng::scene::Format* get_scene_format(){return sce_format;}
  inline eng::scene::Database* get_scene_database(){return sce_database;}
  inline eng::scene::Loader* get_scene_loader(){return sce_loader;}
  inline eng::scene::Glyph* get_scene_glyph(){return sce_glyph;}
  inline eng::scene::Bookmark* get_scene_bookmark(){return sce_bookmark;}
  inline eng::scene::Entity* get_scene_entity(){return sce_entity;}

private:
  //Dependancy
  eng::Node* node_engine;
  vk::Node* node_vulkan;

  //Child
  eng::scene::Parameter* sce_param;
  eng::scene::Database* sce_database;
  eng::scene::Glyph* sce_glyph;
  eng::scene::Loader* sce_loader;
  eng::scene::Format* sce_format;
  eng::scene::Bookmark* sce_bookmark;
  eng::scene::gui::Scene* gui_scene;
  eng::scene::gui::Loader* gui_loader;
  eng::scene::Entity* sce_entity;

  bool show_scene = true;
  bool show_loader = true;
};

}
