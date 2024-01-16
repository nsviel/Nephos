#pragma once

#include <Utility/Base/Entity/Struct_entity.h>

#include <string>
#include <vector>
#include <list>
#include <iostream>


namespace eng::base{

//Set are entity container
struct Set
{
  //---------------------------

  Set(std::string name);
  void reset();
  void add_new_set(std::string name);
  void set_visibility(bool value);
  void select_next_entity();
  void insert_entity(eng::base::Entity* entity);
  void remove_entity(eng::base::Entity* entity);
  eng::base::Set* get_set(std::string name);
  eng::base::Entity* get_entity(std::string name);

  //Info
  std::string name;
  bool is_visible = true;
  int nb_entity = 0;
  int nb_set = 0;
  int ID_entity = 0;

  //Data
  eng::base::Entity* selected_entity = nullptr;
  std::list<eng::base::Entity*> list_entity;
  std::list<eng::base::Set*> list_set;

  //---------------------------
};

}
