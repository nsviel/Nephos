#pragma once

#include <Utility/Base/Class/Node.h>

namespace io{class Node;}
namespace io::exp{class Structure;}
namespace io::exp{class Exporter;}
namespace io::exp::gui{class Panel;}
namespace dat{class Node;}


namespace io::exp{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(io::Node* node_io);
  ~Node();

public:
  //Main function
  void gui();

  inline dat::Node* get_node_data(){return node_data;}

  inline io::exp::Structure* get_io_struct(){return io_struct;}
  inline io::exp::Exporter* get_io_exporter(){return io_exporter;}

private:
  //Dependancy
  dat::Node* node_data;

  //Child
  io::exp::Structure* io_struct;
  io::exp::Exporter* io_exporter;
  io::exp::gui::Panel* gui_export;
};

}
