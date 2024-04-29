#pragma once

#include <Utility/Specific/Common.h>

namespace vk::main{class Engine;}
namespace sce{class Node;}
namespace gly{class Node;}
namespace sce{class Operation;}
namespace sce{class Database;}


namespace sce{

class Entity
{
public:
  //Constructor / Destructor
  Entity(sce::Node* node_scene);
  ~Entity();

public:
  //Main function
  void init_entity(utl::type::Entity* entity);
  void clear_entity(utl::type::Entity* entity);

private:
  sce::Node* node_scene;
  vk::main::Engine* vk_engine;
  sce::Database* sce_database;
  gly::Node* node_glyph;
};

}
