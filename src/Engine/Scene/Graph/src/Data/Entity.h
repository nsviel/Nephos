#pragma once

#include <Utility/Specific/Common.h>

namespace vk::main{class Engine;}
namespace scene{class Node;}
namespace gly{class Node;}
namespace scene{class Operation;}
namespace scene{class Database;}


namespace scene{

class Entity
{
public:
  //Constructor / Destructor
  Entity(scene::Node* node_scene);
  ~Entity();

public:
  //Main function
  void init_entity(utl::type::Entity* entity);
  void clear_entity(utl::type::Entity* entity);

private:
  scene::Node* node_scene;
  vk::main::Engine* vk_engine;
  scene::Database* sce_database;
  gly::Node* sce_glyph;
};

}
