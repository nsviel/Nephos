#pragma once

#include <vector>

namespace cam{class Entity;}
namespace dat::graph{class Node;}
namespace dat::element{class Set;}
namespace dat{class Structure;}
namespace dat::base{class Set;}
namespace dat::base{class Entity;}
namespace utl::base{class Element;}


namespace dat::graph{

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

  //Accesseur
  dat::base::Set* get_set_main();
  dat::base::Set* get_set_graph();
  dat::base::Set* get_set_scene();

private:
  dat::Node* node_data;
  dat::element::Set* dat_set;
  dat::Structure* dat_struct;
};

}
