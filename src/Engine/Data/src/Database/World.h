#pragma once

#include <Engine/Data/Namespace.h>
#include <Utility/Specific/common.h>

class VK_engine;

namespace eng::scene{
class Database;


class World
{
public:
  //Constructor / Destructor
  World(eng::scene::Node* sce_node);
  ~World();

public:
  //Main function
  void init();

  //Entity function
  void import_entity(utl::type::Entity* entity);
  void init_entity(utl::type::Entity* entity);
  void update_entity(utl::type::Entity* entity);

  inline utl::type::Set* get_set_world(){return set_world;}

private:
  VK_engine* vk_engine;
  eng::scene::Database* sce_database;

  utl::type::Set* set_world;
};

}
