#pragma once

namespace prf{class Node;}
namespace dat{class Node;}
namespace eng{class Node;}
namespace rad{class Node;}
namespace io{class Node;}


namespace rsx{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(eng::Node* node_engine);
  ~Node();

public:
  //Main function
  void config();
  void init();

  inline eng::Node* get_node_engine(){return node_engine;}
  inline prf::Node* get_node_profiler(){return node_profiler;}
  inline dat::Node* get_node_data(){return node_data;}

private:
  //Dependancy
  io::Node* node_io;
  eng::Node* node_engine;
  prf::Node* node_profiler;
  rad::Node* node_radio;
  dat::Node* node_data;

  //Child
};

}
