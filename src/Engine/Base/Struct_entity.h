#pragma once


namespace eng::structure{

struct Entity
{
  //---------------------------

  virtual ~Entity(){}
  virtual void reset(){};

  bool is_visible = true;
  bool is_suppressible = true;

  //---------------------------
};

}
