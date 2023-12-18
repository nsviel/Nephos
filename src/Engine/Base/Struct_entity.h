#pragma once

#include <string>


namespace eng::structure{

struct Entity
{
  //---------------------------

  virtual ~Entity(){}
  virtual void reset(){};

  int ID = -1;
  bool is_visible = true;
  bool is_suppressible = true;
  std::string name = "";

  //---------------------------
};

}
