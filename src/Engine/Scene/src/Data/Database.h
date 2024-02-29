#pragma once

#include <Utility/Specific/common.h>

namespace eng::scene{class Node;}


namespace eng::scene{

class Database
{
public:
  //Constructor / Destructor
  Database(eng::scene::Node* node_scene);
  ~Database();

  //Main function
  void init();

  //Subfunction
  void assign_UID(utl::type::Entity* entity);
  void assign_UID(utl::type::Data* data);

  inline utl::type::Set* get_set_main(){return set_main;}
  inline utl::type::Set* get_set_scene(){return set_scene;}
  inline utl::type::Set* get_set_world(){return set_world;}

private:
  utl::type::Set* set_main;
  utl::type::Set* set_scene;
  utl::type::Set* set_world;
};

}
