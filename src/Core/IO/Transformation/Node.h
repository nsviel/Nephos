#pragma once

#include <Utility/Base/Class/Node.h>

namespace vk{class Node;}
namespace dat{class Node;}
namespace core{class Node;}
namespace dyn{class Node;}
namespace io::trf{class Structure;}
namespace io::trf{class Transformation;}
namespace io::trf::gui{class Panel;}


namespace io::trf{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(core::Node* node_core);
  ~Node();

public:
  void init();
  void gui();

  inline core::Node* get_node_core(){return node_core;}
  inline vk::Node* get_node_vulkan(){return node_vulkan;}
  inline dat::Node* get_node_data(){return node_data;}
  inline dyn::Node* get_node_dynamic(){return node_dynamic;}

  inline io::trf::Structure* get_io_struct(){return io_struct;}
  inline io::trf::Transformation* get_io_transformation(){return io_transformation;}

private:
  //Dependancy
  core::Node* node_core;
  vk::Node* node_vulkan;
  dat::Node* node_data;
  dyn::Node* node_dynamic;

  //Child
  io::trf::Structure* io_struct;
  io::trf::Transformation* io_transformation;
  io::trf::gui::Panel* gui_transformation;
};

}
