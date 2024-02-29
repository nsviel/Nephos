#pragma once

#include <Utility/Specific/common.h>


namespace eng::scene{

class Set
{
public:
  //Constructor / Destructor
  Set();
  ~Set();

public:
  //Set function
  void update_set(utl::type::Set* set);
  void reset_set(utl::type::Set* set);
  void visibility_set(utl::type::Set* set, bool value);

  //Subset function
  void add_subset(utl::type::Set* set, utl::type::Set* subset);
  utl::type::Set* create_subset(utl::type::Set* set, std::string name);
  utl::type::Set* get_subset(utl::type::Set* set, std::string name);
  utl::type::Set* get_or_create_subset(utl::type::Set* set, string name);

  //Entity function
  void insert_entity(utl::type::Set* set, utl::type::Entity* entity);
  void delete_entity(utl::type::Set* set, utl::type::Entity* entity);
  void delete_entity_all(utl::type::Set* set);
  void select_entity_next(utl::type::Set* set);
  void select_entity(utl::type::Set* set, utl::type::Entity* entity);
  bool is_selected_entity(utl::type::Set* set, utl::type::Entity* entity);

  //Subfunction
  int compute_number_entity(utl::type::Set* set);
  int compute_number_point(utl::type::Set* set);

private:

};

}
