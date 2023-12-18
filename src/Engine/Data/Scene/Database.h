#pragma once

#include <Engine/Base/Namespace.h>
#include <Engine/Data/Namespace.h>
#include <Utility/Specific/common.h>

namespace eng::data{
class Node;


class Database
{
public:
  //Constructor / Destructor
  Database(eng::data::Node* eng_data);
  ~Database();

  //Main function
  void init_set();
  void add_new_set(string name);
  void assign_ID(eng::structure::Entity* entity);
  eng::structure::Set* get_set(string name);

  inline list<eng::structure::Set*>* get_list_set(){return &list_set;}

private:
  list<eng::structure::Set*> list_set;
  int ID_entity;
};

}
