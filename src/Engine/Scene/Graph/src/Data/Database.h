#pragma once

#include <Utility/Specific/Common.h>

namespace scene{class Node;}
namespace scene{class Set;}


namespace scene{

class Database
{
public:
  //Constructor / Destructor
  Database(scene::Node* node_scene);
  ~Database();

  //Main function
  void init();
  void loop();
  void reset();
  void clean();

  //Subfunction
  void assign_UID(utl::type::Entity* entity);
  void assign_UID(utl::type::Data* data);

  inline utl::type::Set* get_set_main(){return set_main;}
  inline utl::type::Set* get_set_scene(){return set_scene;}
  inline utl::type::Set* get_set_world(){return set_world;}

private:
  scene::Set* sce_set;

  utl::type::Set* set_main;
  utl::type::Set* set_scene;
  utl::type::Set* set_world;
};

}