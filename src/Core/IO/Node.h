#pragma once

#include <Utility/Base/Class/Node.h>

namespace core{class Node;}
namespace dat{class Node;}
namespace io::imp{class Node;}
namespace io::exp{class Node;}


namespace io{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(core::Node* node_core);
  ~Node();

public:
  //Main function
  void init();
  void gui();

  inline dat::Node* get_node_data(){return node_data;}
  inline io::imp::Node* get_node_importer(){return node_importer;}
  inline io::exp::Node* get_node_exporter(){return node_exporter;}

private:
  //Dependancy
  dat::Node* node_data;

  //Child
  io::imp::Node* node_importer;
  io::exp::Node* node_exporter;
};

}
