#pragma once


#include <Engine/Scene/Namespace.h>

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
  void assign_ID(utl::type::Entity* entity);
  void assign_ID(utl::type::Data* entity);

  inline utl::type::Set* get_data_set(){return data_set;}

private:
  utl::type::Set* data_set;
};

}
