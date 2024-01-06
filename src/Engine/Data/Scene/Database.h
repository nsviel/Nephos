#pragma once

#include <Engine/Base/Namespace.h>
#include <Engine/Data/Namespace.h>
#include <Utility/Specific/common.h>

namespace eng::scene{
class Node;


class Database
{
public:
  //Constructor / Destructor
  Database(eng::scene::Node* eng_data);
  ~Database();

  //Main function
  void init_set();
  void assign_ID(eng::structure::Entity* entity);

  inline eng::structure::Set* get_data_set(){return data_set;}

private:
  eng::structure::Set* data_set;
};

}
