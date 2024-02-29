#pragma once

#include <Utility/Specific/common.h>

namespace vk::main{class Graphical;}
namespace eng::scene{class Node;}
namespace eng::scene{class Database;}


namespace eng::scene{

class World
{
public:
  //Constructor / Destructor
  World(eng::scene::Node* node_scene);
  ~World();

public:
  //Main function
  void init();

  //Entity function
  void init_entity(utl::type::Entity* entity);

  inline utl::type::Set* get_set_world(){return set_world;}

private:
  vk::main::Graphical* vk_graphical;
  eng::scene::Database* sce_database;

  utl::type::Set* set_world;
};

}
