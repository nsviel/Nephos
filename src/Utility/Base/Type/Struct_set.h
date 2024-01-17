#pragma once

#include <Utility/Specific/common.h>
#include <Utility/Base/Entity/Struct_entity.h>
#include <image/IconsFontAwesome6.h>

namespace utl::type{
class Entity;


//Set are entity container
struct Set
{
  //---------------------------

  //Constructor
  Set();
  Set(std::string name);

  //Main function
  void update();
  void reset();

  //Add element
  void add_set(utl::type::Set* set);
  void add_new_set(std::string name);
  void select_next_entity();
  void insert_entity(utl::type::Entity* entity);
  void remove_entity(utl::type::Entity* entity);

  //Parameter
  void set_visibility(bool value);
  utl::type::Set* get_set(std::string name);
  utl::type::Entity* get_entity(std::string name);

  //Info
  std::string name;
  std::string type = "set";
  std::string icon = ICON_FA_FOLDER;
  bool is_visible = true;
  int nb_entity = 0;
  int nb_set = 0;
  int UID = 0;

  //Data
  utl::type::Entity* selected_entity = nullptr;
  std::list<utl::type::Entity*> list_entity;
  std::list<utl::type::Set*> list_set;
  utl::type::Set* set_parent = nullptr;

  //---------------------------
};

}
