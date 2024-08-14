#pragma once

#include <vector>

namespace cam{class Entity;}
namespace dat::elm{class Set;}
namespace dat::graph{class Node;}
namespace dat::graph{class Graph;}
namespace dat::graph{class Structure;}
namespace dat::base{class Set;}
namespace dat::base{class Entity;}
namespace utl::base{class Element;}


namespace dat::graph{

class Selection
{
public:
  //Constructor / Destructor
  Selection(dat::graph::Node* node_graph);
  ~Selection();

public:
  //Main function
  void select_element(utl::base::Element* element);
  void select_next_element();

  //Accesseur
  utl::base::Element* get_selected_element();
  dat::base::Entity* get_selected_entity();
  dat::base::Set* get_selected_set();

private:
  dat::graph::Graph* dat_graph;
  dat::elm::Set* dat_set;
  dat::graph::Structure* dat_struct;
};

}
