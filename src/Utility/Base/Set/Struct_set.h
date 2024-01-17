#pragma once

#include <Utility/Base/Entity/Struct_entity.h>

#include <string>
#include <vector>
#include <list>
#include <iostream>


namespace utl::base{

//Set are entity container
struct Set
{
  //---------------------------

  Set();
  Set(std::string name);
  void reset();
  void add_new_set(std::string name);
  void set_visibility(bool value);
  void select_next_entity();
  void insert_entity(entity::Entity* entity);
  void remove_entity(entity::Entity* entity);
  utl::base::Set* get_set(std::string name);
  entity::Entity* get_entity(std::string name);

  //Info
  std::string name;
  std::string type = "set";
  bool is_visible = true;
  int nb_entity = 0;
  int nb_set = 0;
  int UID = 0;

  //Data
  entity::Entity* selected_entity = nullptr;
  std::list<entity::Entity*> list_entity;
  std::list<utl::base::Set*> list_set;

  //---------------------------
};

}
