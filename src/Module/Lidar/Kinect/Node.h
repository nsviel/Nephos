#pragma once

#include <Utility/Specific/Common.h>

namespace prf{class Node;}
namespace dat{class Node;}
namespace eng{class Node;}
namespace ldr{class Node;}
namespace dat{class Graph;}
namespace utl::thread{class Pool;}
namespace k4n::capture{class Connection;}
namespace k4n::utils{class Configuration;}
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
  inline prf::Node* get_node_profiler(){return node_profiler;}
  inline dat::Node* get_node_data(){return node_data;}
  inline k4n::Structure* get_k4n_structure(){return k4n_structure;}

private:
  //Dependancy
  ldr::Node* node_loader;
  eng::Node* node_engine;
  prf::Node* node_profiler;
  dat::Node* node_data;

  //Child
  utl::thread::Pool* thread_pool;
  k4n::capture::Connection* k4n_connection;
  k4n::utils::Configuration* k4n_config;
  k4n::Structure* k4n_structure;
};

}
