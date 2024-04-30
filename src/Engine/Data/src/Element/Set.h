#pragma once

#include <string>

namespace dat{class Node;}
namespace dat{class Structure;}
namespace dat::base{class Set;}
namespace dat::base{class Entity;}


namespace dat{

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
  void remove_entity_all(dat::base::Set* set);
  void select_entity_next(dat::base::Set* set);
  void select_entity(dat::base::Set* set, dat::base::Entity* entity);
  bool is_selected_entity(dat::base::Set* set, dat::base::Entity* entity);

  //Subfunction
  int compute_number_entity(dat::base::Set* set);
  int compute_number_point(dat::base::Set* set);

private:
  dat::Structure* dat_struct;
};

}
