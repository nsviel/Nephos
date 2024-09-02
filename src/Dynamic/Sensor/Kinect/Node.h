#pragma once

#include <Utility/Base/Class/Node.h>

namespace dyn::sen{class Node;}
namespace dat{class Node;}
namespace io{class Node;}
namespace dyn::prc{class Node;}
namespace dat::gph{class Graph;}
namespace thr::task{class Pool;}

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

  inline dat::Node* get_node_data(){return node_data;}
  inline io::Node* get_node_io(){return node_io;}
  inline dyn::prc::Node* get_node_processing(){return node_processing;}

  inline k4n::Structure* get_k4n_structure(){return k4n_structure;}

private:
  //Dependancy
  io::Node* node_io;
  dyn::prc::Node* node_processing;
  dat::Node* node_data;
  thr::task::Pool* thread_pool;

  //Child
  k4n::capture::Connection* k4n_connection;
  k4n::Structure* k4n_structure;
};

}
