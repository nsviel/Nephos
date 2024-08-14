#pragma once

#include <Utility/Base/Class/Node.h>

namespace eng{class Node;}
namespace io::imp{class Node;}
namespace io::exp{class Node;}


namespace io{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(eng::Node* node_engine);
  ~Node();

public:
  inline io::imp::Node* get_node_importer(){return node_importer;}
  inline io::exp::Node* get_node_exporter(){return node_exporter;}

private:
  io::imp::Node* node_importer;
  io::exp::Node* node_exporter;
};

}
