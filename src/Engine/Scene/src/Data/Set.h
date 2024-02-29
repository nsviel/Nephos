#pragma once

#include <Utility/Specific/common.h>

namespace eng::scene{class Node;}


namespace eng::scene{

class Set
{
public:
  //Constructor / Destructor
  Set(eng::scene::Node* node_scene);
  ~Set();

public:
  //Set function
  void update_set(utl::type::Set* set);
  void reset_set(utl::type::Set* set);

  //Entity function
  void delete_entity_all(utl::type::Set* set);
  void delete_entity_selected(utl::type::Set* set);
  void select_entity_next(utl::type::Set* set);

  //Subfunction
  int compute_number_entity(utl::type::Set* set);
  int compute_number_point(utl::type::Set* set);

private:

};

}
