#pragma once

#include <Utility/Base/Class/Node.h>

namespace dyn::sen{class Node;}
namespace dyn::prc{class Node;}
namespace dat{class Node;}
namespace io{class Node;}

namespace k4n{class Structure;}
namespace k4n{class Importer;}


namespace k4n{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(dyn::sen::Node* node_sensor);
  ~Node();

public:
  //Main function

  inline dyn::prc::Node* get_node_processing(){return node_processing;}
  inline dat::Node* get_node_data(){return node_data;}
  inline io::Node* get_node_io(){return node_io;}

  inline k4n::Structure* get_k4n_structure(){return k4n_structure;}

private:
  //Dependancy
  dyn::prc::Node* node_processing;
  dat::Node* node_data;
  io::Node* node_io;

  //Child
  k4n::Structure* k4n_structure;
  k4n::Importer* k4n_importer;
};

}
