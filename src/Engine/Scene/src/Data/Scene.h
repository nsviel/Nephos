#pragma once

#include <Utility/Specific/common.h>

namespace vk::main{class Graphical;}
namespace eng::scene{class Node;}
namespace eng::scene{class Glyph;}
namespace eng::scene{class Operation;}
namespace eng::scene{class Database;}


namespace eng::scene{

class Scene
{
public:
  //Constructor / Destructor
  Scene(eng::scene::Node* node_scene);
  ~Scene();

public:
  //Main function
  void init();
  void loop();
  void reset();

  inline void set_selected_entity(utl::type::Entity* entity){set_scene->selected_entity = entity;}

private:
  vk::main::Graphical* vk_graphical;
  eng::scene::Database* sce_database;
  eng::scene::Glyph* sce_glyph;

  utl::type::Set* set_scene;
};

}
