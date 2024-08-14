#pragma once

#include <string>

namespace dat{class Node;}
namespace dat{class Structure;}
namespace dat::element{class Entity;}
namespace dat::graph{class UID;}
namespace dat::base{class Set;}
namespace dat::base{class Entity;}
namespace dat::base{class Glyph;}


namespace dat::element{

class Set
{
public:
  //Constructor / Destructor
  Set(dat::Node* node_data);
  ~Set();

public:
  //Set function
  void update_set(dat::base::Set* set);
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
  dat::Node* node_data;
  dat::Structure* dat_struct;
  dat::element::Entity* dat_entity;
  dat::graph::UID* dat_uid;
};

}