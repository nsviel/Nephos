#pragma once

#include <Utility/Specific/Common.h>

namespace prf{class Node;}
namespace dat{class Node;}
namespace eng{class Node;}
namespace k4n::capture{class Connection;}
namespace utl::thread{class Pool;}
namespace k4n::calibration{class Model;}
namespace rad{class Node;}
namespace ldr{class Node;}
namespace dat{class Graph;}


namespace rsx{

class Node : public utl::type::Node
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
  inline rad::Node* get_node_radio(){return node_radio;}

private:
  //Dependancy
  ldr::Node* node_loader;
  eng::Node* node_engine;
  prf::Node* node_profiler;
  rad::Node* node_radio;
  dat::Node* node_data;

  //Child
  utl::thread::Pool* thread_pool;
  k4n::capture::Connection* k4n_connection;
};

}
