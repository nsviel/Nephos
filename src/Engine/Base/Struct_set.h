#pragma once

#include <Engine/Base/Struct_entity.h>

#include <string>
#include <vector>
#include <list>


namespace eng::structure{

//Set are entity container
struct Set
{
  //---------------------------

  Set(std::string name);
  void set_visibility(bool value);

  //Info
  std::string name;
  int nb_entity = 0;
  bool is_visible = true;

  //Data
  eng::structure::Entity* selected_entity = nullptr;
  std::list<eng::structure::Entity*> list_obj;
  std::list<eng::structure::Set*> list_set;

  //---------------------------
};

}
