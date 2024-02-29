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

  //Entity function
  void insert_entity(utl::type::Set* set, utl::type::Entity* entity);
  void delete_entity(utl::type::Set* set, utl::type::Entity* entity);
  void delete_entity_all(utl::type::Set* set);
  void select_entity_next(utl::type::Set* set);
  void select_entity(utl::type::Set* set, utl::type::Entity* entity);

  //Subfunction
  int compute_number_entity(utl::type::Set* set);
  int compute_number_point(utl::type::Set* set);

private:

};

}
