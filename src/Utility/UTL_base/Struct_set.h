#pragma once

#include <Engine/Base/Struct_object.h>
#include <UTL_base/Struct_object.h>
#include <string>
#include <vector>
#include <list>


namespace data{

//Collection are cloud containers
struct Set{
  //---------------------------

  Set(std::string name);
  void reset();

  //Info
  std::string name;
  int nb_object = 0;
  bool is_visible = true;

  //Data
  eng::structure::Object* selected_obj = nullptr;
  std::list<eng::structure::Object*> list_obj;
  std::list<data::Set*> list_set;

  //---------------------------
};

}
