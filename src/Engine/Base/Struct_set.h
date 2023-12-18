#pragma once

#include <Engine/Base/Struct_object.h>

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
  int nb_object = 0;
  bool is_visible = true;

  //Data
  eng::structure::Object* selected_obj = nullptr;
  std::list<eng::structure::Object*> list_obj;
  std::list<eng::structure::Set*> list_set;

  //---------------------------
};

}
