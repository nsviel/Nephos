#pragma once

#include <vector>

namespace cam{class Entity;}
namespace dat{class Node;}
namespace dat::graph{class Node;}
namespace dat::graph{class Structure;}
namespace dat::elm{class Set;}
namespace dat::base{class Set;}
namespace dat::base{class Entity;}
namespace utl::base{class Element;}


namespace dat::graph{

class Graph
{
public:
  //Constructor / Destructor
  Graph(dat::graph::Node* node_graph);
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
  dat::elm::Set* dat_set;
  dat::graph::Structure* dat_struct;
};

}
