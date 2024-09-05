#pragma once

#include <Utility/Base/Class/Node.h>

namespace io{class Node;}
namespace io::imp{class Importer;}
namespace io::exp{class Exporter;}


namespace fmt{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(io::Node* node_io);
  ~Node();

public:
  //Main function
  void init();

private:
  io::imp::Importer* io_importer;
  io::exp::Exporter* io_exporter;
};

}
