#pragma once

#include <vector>

namespace cam{class Entity;}
namespace dat{class Node;}
namespace dat{class Set;}
namespace dat{class Structure;}
namespace dat::base{class Set;}
namespace dat::base{class Entity;}
namespace utl::base{class Element;}


namespace dat{

class Graph
{
public:
  //Constructor / Destructor
  Graph(dat::Node* node_data);
  ~Graph();

  //Main function
  void init();
  void loop();
  void reset();
  void clean();

  //Subfunction
  void select_element(utl::base::Element* element);
  void remove_selected_element();
  void select_next_element();
  void assign_UID(utl::base::Element* element);

  //Accesseur
  utl::base::Element* get_selected_element();
  dat::base::Entity* get_selected_entity();
  dat::base::Set* get_selected_set();
  dat::base::Set* get_set_main();
  dat::base::Set* get_set_graph();
  dat::base::Set* get_set_scene();

private:
  dat::Node* node_data;
  dat::Set* dat_set;
  dat::Structure* dat_struct;

  std::vector<cam::Entity*> vec_camera;
};

}
