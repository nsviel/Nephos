#pragma once

#include <Utility/Specific/common.h>
#include <image/IconsFontAwesome6.h>

namespace utl::type{class Entity;}


namespace utl::type{

class Set
{
public:
  Set();
  Set(std::string name);
  ~Set(){}

public:
  //Main function
  void update();
  void reset();

  //Set function
  void add_set(utl::type::Set* set);
  void add_new_set(std::string name);

  //Entity function
  void insert_entity(utl::type::Entity* entity);
  void delete_entity(utl::type::Entity* entity);
  void delete_entity_all();
  void delete_entity_selected();
  void select_next_entity();
  void set_selected_entity(utl::type::Entity* entity);

  //Subfunction
  void set_visibility(bool value);
  int compute_number_point();
  utl::type::Set* get_set(std::string name);
  utl::type::Entity* get_entity(std::string name);

  inline int get_nb_entity(){return list_entity.size();}
  inline bool is_selected_entity(utl::type::Entity* entity){return entity->UID == selected_entity->UID;}
  inline utl::type::Entity* get_selected_entity(){return selected_entity;}

public:
  //Info
  int UID = 0;
  int nb_entity = 0;
  int nb_set = 0;
  bool is_visible = true;
  bool is_lockable = false;
  bool is_locked = false;
  bool is_suppressible = false;
  std::string name;
  std::string type = "set";
  std::string icon = ICON_FA_FOLDER;

  //Data
  utl::type::Pose pose;
  utl::type::Entity* selected_entity = nullptr;
  utl::type::Set* selected_set = this;
  utl::type::Set* set_parent = nullptr;
  std::list<utl::type::Entity*> list_entity;
  std::list<utl::type::Set*> list_subset;
};

}
