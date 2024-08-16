#pragma once

#include <Utility/Base/Class/Node.h>

namespace vk{class Node;}
namespace dat{class Node;}
namespace core{class Node;}
namespace dyn::prc{class Node;}
namespace io::exp{class Structure;}
namespace io::exp{class Exporter;}
namespace io::exp::gui{class Panel;}


namespace io::exp{

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

  inline core::Node* get_node_core(){return node_core;}
  inline vk::Node* get_node_vulkan(){return node_vulkan;}
  inline dat::Node* get_node_data(){return node_data;}
  inline dyn::Node* get_node_dynamic(){return node_dynamic;}

  inline io::exp::Structure* get_io_struct(){return io_struct;}
  inline io::exp::Exporter* get_io_exporter(){return io_exporter;}

private:
  //Dependancy
  core::Node* node_core;
  vk::Node* node_vulkan;
  dat::Node* node_data;
  dyn::Node* node_dynamic;

  //Child
  io::exp::Structure* io_struct;
  io::exp::Exporter* io_exporter;
  io::exp::gui::Panel* gui_export;
};

}
