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
  std::string name = "";

  //---------------------------
};

}
