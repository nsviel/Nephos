#pragma once

#include <Utility/Base/Class/Node.h>

namespace dyn::sen{class Node;}
namespace dat{class Node;}
namespace core{class Node;}
namespace io{class Node;}
namespace dyn{class Node;}
namespace dat::gph{class Graph;}
namespace sys::thread::task{class Pool;}

namespace k4n::capture{class Connection;}
namespace k4n{class Structure;}


namespace k4n{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(dyn::sen::Node* node_sensor);
  ~Node();

public:
  //Main function
  void init();
  void clean();
  void loop();

  inline core::Node* get_node_core(){return node_core;}
  inline dat::Node* get_node_data(){return node_data;}
  inline io::Node* get_node_io(){return node_io;}
  inline dyn::Node* get_node_dynamic(){return node_dynamic;}
  
  inline k4n::Structure* get_k4n_structure(){return k4n_structure;}

private:
  //Dependancy
  io::Node* node_io;
  core::Node* node_core;
  dat::Node* node_data;
  dyn::Node* node_dynamic;
  sys::thread::task::Pool* thread_pool;

  //Child
  k4n::capture::Connection* k4n_connection;
  k4n::Structure* k4n_structure;
};

}
