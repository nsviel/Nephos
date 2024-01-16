#pragma once

#include <string>


namespace eng::base{

struct Entity
{
  //---------------------------

  virtual ~Entity(){}
  virtual void update_entity(){}
  virtual void remove_entity(){}
  virtual void reset_entity(){}
  virtual void visibility_entity(bool value){}

  int ID = -1;
  bool is_visible = true;
  bool is_suppressible = true;
  bool is_permanent = false;
  bool is_movable = true;
  std::string name = "";
  std::string type = "entity";

  inline void set_visibility(bool value){this->is_visible = value;}

  //---------------------------
};

}
