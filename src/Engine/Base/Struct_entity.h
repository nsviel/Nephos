#pragma once


namespace eng::structure{

struct Entity
{
  //---------------------------

  virtual ~Entity(){}

  bool is_visible = true;
  bool is_suppressible = true;

  //---------------------------
};

}
