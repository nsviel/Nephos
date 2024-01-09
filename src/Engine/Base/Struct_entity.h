#pragma once

#include <string>


namespace eng::data{

struct Entity
{
  //---------------------------

  virtual ~Entity(){}
  virtual void reset(){};

  int ID = -1;
  bool is_visible = true;
  bool is_suppressible = true;
  bool is_permanent = false;
  bool is_movable = true;
  std::string name = "";
  std::string type = "entity";

  //---------------------------
};

}
