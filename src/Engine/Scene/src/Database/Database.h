#pragma once

#include <Utility/Specific/common.h>

namespace eng::scene{class Node;}


namespace eng::scene{

class Database
{
public:
  //Constructor / Destructor
  Database(eng::scene::Node* sce_node);
  ~Database();

  //Main function
  void init_set();
  void assign_UID(utl::type::Entity* entity);
  void assign_UID(utl::type::Data* entity);

  inline utl::type::Set* get_data_set(){return data_set;}

private:
  utl::type::Set* data_set;
};

}
