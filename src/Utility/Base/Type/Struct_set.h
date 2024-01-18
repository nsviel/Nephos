#pragma once

#include <Utility/Specific/common.h>
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

  //Entity addition
  void add_set(utl::type::Set* set);
  void add_new_set(std::string name);
  void insert_entity(utl::type::Entity* entity);
  void delete_entity(utl::type::Entity* entity);
  void delete_entity_all();

  //Entity selection
  void select_next_entity();
  void set_selected_entity(utl::type::Entity* entity);

  //Parameter
  void set_visibility(bool value);
  utl::type::Set* get_set(std::string name);
  utl::type::Entity* get_entity(std::string name);

  inline bool is_selected_entity(utl::type::Entity* entity){return entity->UID == selected_entity->UID;}
  inline utl::type::Entity* get_selected_entity(){return selected_entity;}

  //Info
  int UID = 0;
  int nb_entity = 0;
  int nb_set = 0;
  bool is_visible = true;
  bool is_lockable = false;
  bool is_locked = false;
  std::string name;
  std::string type = "set";
  std::string icon = ICON_FA_FOLDER;

  //Data
  utl::type::Entity* selected_entity = nullptr;
  utl::type::Set* set_parent = nullptr;
  std::list<utl::type::Entity*> list_entity;
  std::list<utl::type::Set*> list_set;

  //---------------------------
};

}
