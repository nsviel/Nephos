#pragma once

#include <Utility/Base/Namespace.h>
#include <Engine/Scene/Namespace.h>
#include <Utility/Base/Namespace.h>
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
  void assign_ID(entity::Entity* entity);

  inline utl::base::Set* get_data_set(){return data_set;}

private:
  utl::base::Set* data_set;
};

}
