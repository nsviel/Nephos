#pragma once

#include <Utility/Specific/Common.h>

namespace dat{class Node;}
namespace dat{class Set;}


namespace dat{

class Database
{
public:
  //Constructor / Destructor
  Database(dat::Node* node_data);
  ~Database();

  //Main function
  void init();
  void loop();
  void reset();
  void clean();

  //Subfunction
  void assign_UID(utl::type::Element* element);

  inline utl::type::Set* get_set_main(){return set_main;}
  inline utl::type::Set* get_set_graph(){return set_graph;}
  inline utl::type::Set* get_set_scene(){return set_scene;}

private:
  dat::Set* dat_set;

  utl::type::Set* set_main;
  utl::type::Set* set_graph;
  utl::type::Set* set_scene;
};

}
