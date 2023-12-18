#pragma once

#include <Engine/Base/Struct_entity.h>

#include <string>
#include <vector>
#include <list>
#include <iostream>


namespace eng::structure{

//Set are entity container
struct Set
{
  //---------------------------

  Set(std::string name);
  void reset();
  void add_new_set(std::string name);
  void set_visibility(bool value);
  void select_next_object();
  eng::structure::Set* get_set(std::string name);
  eng::structure::Entity* get_entity(std::string name);

  //Info
  std::string name;
  bool is_visible = true;
  int nb_entity = 0;
  int nb_set = 0;
  int ID_entity = 0;

  //Data
  eng::structure::Entity* selected_entity = nullptr;
  std::list<eng::structure::Entity*> list_entity;
  std::list<eng::structure::Set*> list_set;

  //---------------------------
};

}
