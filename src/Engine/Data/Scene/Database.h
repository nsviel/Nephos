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
  Database(eng::scene::Node* node_scene);
  ~Database();

  //Main function
  void init_set();
  void assign_ID(eng::data::Entity* entity);

  inline eng::data::Set* get_data_set(){return data_set;}

private:
  eng::data::Set* data_set;
};

}
