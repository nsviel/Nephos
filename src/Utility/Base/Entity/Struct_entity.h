#pragma once

#include <Utility/Base/Data.h>
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

  inline bool get_visibility(){return is_visible;}

  //---------------------------
};

}
