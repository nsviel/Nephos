#pragma once

#include <Utility/Base/Class/Node.h>

namespace dat{class Node;}
namespace eng{class Node;}
namespace ldr{class Node;}
namespace dyn{class Node;}
namespace dat{class Graph;}
namespace utl::thread::task{class Pool;}
namespace k4n::capture{class Connection;}
namespace k4n{class Structure;}


namespace k4n{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(eng::Node* node_engine);
  ~Node();

public:
  //Main function
  void init();
  void clean();
  void loop();

  inline eng::Node* get_node_engine(){return node_engine;}
  inline dat::Node* get_node_data(){return node_data;}
  inline ldr::Node* get_node_loader(){return node_loader;}
  inline dyn::Node* get_node_dynamic(){return node_dynamic;}
  inline k4n::Structure* get_k4n_structure(){return k4n_structure;}

private:
  //Dependancy
  ldr::Node* node_loader;
  eng::Node* node_engine;
  dat::Node* node_data;
  dyn::Node* node_dynamic;

  //Child
  utl::thread::task::Pool* thread_pool;
  k4n::capture::Connection* k4n_connection;
  k4n::Structure* k4n_structure;
};

}
