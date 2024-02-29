#pragma once

#include <Utility/Specific/common.h>

namespace vk::main{class Graphical;}
namespace eng::scene{class Node;}
namespace eng::scene{class Glyph;}
namespace eng::scene{class Operation;}
namespace eng::scene{class Database;}


namespace eng::scene{

class Entity
{
public:
  //Constructor / Destructor
  Entity(eng::scene::Node* node_scene);
  ~Entity();

public:
  //Main function
  void init_entity(utl::type::Entity* entity);
  void clear_entity(utl::type::Entity* entity);

private:
  eng::scene::Node* node_scene;
  vk::main::Graphical* vk_graphical;
  eng::scene::Database* sce_database;
  eng::scene::Glyph* sce_glyph;
};

}
