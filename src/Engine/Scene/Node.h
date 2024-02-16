#pragma once

#include <Utility/Specific/common.h>

namespace eng{class Node;}
namespace eng::scene{class Parameter;}
namespace eng::scene{class Scene;}
namespace eng::scene{class Database;}
namespace eng::scene{class Loader;}
namespace eng::scene{class Format;}
namespace eng::scene{class Glyph;}
namespace eng::scene{class Operation;}
namespace eng::scene{class Bookmark;}
namespace eng::scene{class World;}
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
  
  inline eng::scene::Parameter* get_scene_param(){return sce_param;}
  inline eng::scene::Scene* get_scene(){return sce_scene;}
  inline eng::scene::Format* get_scene_format(){return sce_format;}
  inline eng::scene::Database* get_scene_database(){return sce_database;}
  inline eng::scene::Loader* get_scene_loader(){return sce_loader;}
  inline eng::scene::Glyph* get_scene_glyph(){return sce_glyph;}
  inline eng::scene::Bookmark* get_scene_bookmark(){return sce_bookmark;}
  inline eng::scene::World* get_scene_world(){return sce_world;}

private:
  //Dependancy
  eng::Node* node_engine;

  //Child
  eng::scene::Parameter* sce_param;
  eng::scene::Scene* sce_scene;
  eng::scene::Database* sce_database;
  eng::scene::Glyph* sce_glyph;
  eng::scene::Loader* sce_loader;
  eng::scene::Format* sce_format;
  eng::scene::Bookmark* sce_bookmark;
  eng::scene::World* sce_world;
  eng::scene::gui::Scene* gui_scene;
  eng::scene::gui::Loader* gui_loader;

  bool show_scene = true;
  bool show_loader = true;
};

}
