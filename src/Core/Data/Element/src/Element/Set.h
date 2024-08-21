#pragma once

#include <string>

namespace dat::elm{class Node;}
namespace dat::elm{class Entity;}
namespace dat::elm{class UID;}
namespace dat::base{class Set;}
namespace dat::base{class Entity;}
namespace dat::base{class Glyph;}


namespace dat::elm{

class Set
{
public:
  //Constructor / Destructor
  Set(dat::elm::Node* node_element);
  ~Set();

public:
  //Set function
  void update_data(dat::base::Set* set);
  void reset_set(dat::base::Set* set);
  void visibility_set(dat::base::Set* set, bool value);

  //Subset function
  void add_subset(dat::base::Set* set, dat::base::Set* subset);
  dat::base::Set* create_subset(dat::base::Set* set, std::string name);
  dat::base::Set* get_subset(dat::base::Set* set, std::string name);
  dat::base::Set* get_or_create_subset(dat::base::Set* set, std::string name);

  //Entity function
  void insert_entity(dat::base::Set* set, dat::base::Entity* entity);
  void remove_entity(dat::base::Set* set, dat::base::Entity* entity);
  void remove_active_entity(dat::base::Set* set);
  void remove_all_entity(dat::base::Set* set);
  void active_next_entity(dat::base::Set* set);
  void active_entity(dat::base::Set* set, dat::base::Entity* entity);
  bool is_entity_active(dat::base::Set* set, dat::base::Entity* entity);

  //Subfunction
  int compute_number_entity(dat::base::Set* set);
  int compute_number_point(dat::base::Set* set);
  bool is_set_empty(dat::base::Set* set);

private:
  dat::elm::Entity* dat_entity;
  dat::elm::UID* dat_uid;
};

}
