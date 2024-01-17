#pragma once

#include <Utility/Base/Type/Namespace.h>
#include <vector>
#include <list>
#include <string>


namespace entity{

struct Entity
{
  //---------------------------

  virtual ~Entity(){}
  virtual void update_entity(){}
  virtual void remove_entity(){}
  virtual void reset_entity(){}
  virtual void visibility_entity(bool value){}
  virtual utl::base::Data* get_data(){return nullptr;}

  int UID = -1;
  bool is_suppressible = true;
  bool is_permanent = false;
  bool is_movable = true;
  bool is_visible = true;
  std::string name = "";
  std::string type = "entity";
  //utl::base::Set* set_parent = nullptr;

  inline bool get_visibility(){return is_visible;}

  //---------------------------
};

}
