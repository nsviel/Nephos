#pragma once

#include <vector>

namespace cam{class Entity;}
namespace dat{class Node;}
namespace dat::element{class Set;}
namespace dat{class Graph;}
namespace dat{class Structure;}
namespace dat::base{class Set;}
namespace dat::base{class Entity;}
namespace utl::base{class Element;}


namespace dat::graph{

class Selection
{
public:
  //Constructor / Destructor
  Selection(dat::Node* node_data);
  ~Selection();

  //Main function
  void select_element(utl::base::Element* element);
  void select_next_element();

  //Accesseur
  utl::base::Element* get_selected_element();
  dat::base::Entity* get_selected_entity();
  dat::base::Set* get_selected_set();

private:
  dat::Graph* dat_graph;
  dat::element::Set* dat_set;
  dat::Structure* dat_struct;
};

}
