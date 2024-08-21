#pragma once

#include <vector>

namespace cam{class Entity;}
namespace dat::elm{class Set;}
namespace dat::gph{class Node;}
namespace dat::gph{class Graph;}
namespace dat::gph{class Structure;}
namespace dat::base{class Set;}
namespace dat::base{class Entity;}
namespace utl::base{class Element;}


namespace dat::gph{

class Selection
{
public:
  //Constructor / Destructor
  Selection(dat::gph::Node* node_graph);
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
  dat::gph::Graph* dat_graph;
  dat::elm::Set* dat_set;
  dat::gph::Structure* gph_struct;
};

}
