#pragma once

#include <Utility/Base/Entity/Struct_entity.h>
#include <image/IconsFontAwesome6.h>
#include <Utility/Specific/common.h>


namespace utl::base{

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
  void add_set(utl::base::Set* set);
  void add_new_set(std::string name);
  void select_next_entity();
  void insert_entity(entity::Entity* entity);
  void remove_entity(entity::Entity* entity);

  //Parameter
  void set_visibility(bool value);
  utl::base::Set* get_set(std::string name);
  entity::Entity* get_entity(std::string name);

  //Info
  std::string name;
  std::string type = "set";
  std::string icon = ICON_FA_FOLDER;
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
