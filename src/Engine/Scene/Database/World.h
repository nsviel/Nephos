#pragma once

#include <Engine/Scene/Namespace.h>
#include <Utility/Specific/common.h>

namespace eng::scene{
class Database;


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
  void import_entity(utl::type::Entity* entity);

  inline utl::type::Set* get_set_world(){return set_world;}

private:
  eng::scene::Database* sce_database;

  utl::type::Set* set_world;
};

}
