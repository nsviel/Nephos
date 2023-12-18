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
  void assign_ID(eng::structure::Entity* entity);

  inline list<eng::structure::Set*>* get_list_set(){return &data_set->list_set;}
  inline eng::structure::Set* get_set(string name){return data_set->get_set(name);}
  inline eng::structure::Set* get_data_set(){return data_set;}

private:
  eng::structure::Set* data_set;
};

}
