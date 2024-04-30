#pragma once

#include <vector>

namespace cam{class Entity;}
namespace dat{class Node;}
namespace dat{class Set;}
namespace dat{class Structure;}
namespace dat::base{class Set;}
namespace utl::type{class Element;}


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
  void assign_UID(utl::type::Element* element);
  dat::base::Set* get_set_main();
  dat::base::Set* get_set_graph();
  dat::base::Set* get_set_scene();

private:
  dat::Set* dat_set;
  dat::Structure* dat_struct;

  std::vector<cam::Entity*> vec_camera;
};

}
