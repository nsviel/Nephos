#pragma once

#include <Engine/Entity/Struct_entity.h>

#include <string>
#include <vector>
#include <list>
#include <iostream>


namespace eng::data{

//Set are entity container
struct Set
{
  //---------------------------

  Set(std::string name);
  void reset();
  void add_new_set(std::string name);
  void set_visibility(bool value);
  void select_next_entity();
  void insert_entity(eng::data::Entity* entity);
  void remove_entity(eng::data::Entity* entity);
  eng::data::Set* get_set(std::string name);
  eng::data::Entity* get_entity(std::string name);

  //Info
  std::string name;
  bool is_visible = true;
  int nb_entity = 0;
  int nb_set = 0;
  int ID_entity = 0;

  //Data
  eng::data::Entity* selected_entity = nullptr;
  std::list<eng::data::Entity*> list_entity;
  std::list<eng::data::Set*> list_set;

  //---------------------------
};

}
