#pragma once

#include <Utility/Base/Class/Node.h>

namespace vk{class Node;}
namespace dat{class Node;}
namespace eng{class Node;}
namespace dyn{class Node;}
namespace io::exp{class Structure;}
namespace io::exp{class Exporter;}
namespace io::exp::gui{class Panel;}


namespace io::exp{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(eng::Node* node_engine);
  ~Node();

public:
  void init();
  void gui();

  inline eng::Node* get_node_engine(){return node_engine;}
  inline vk::Node* get_node_vulkan(){return node_vulkan;}
  inline dat::Node* get_node_data(){return node_data;}
  inline dyn::Node* get_node_dynamic(){return node_dynamic;}
  inline io::imp::Node* get_node_importer(){return node_importer;}

  inline io::exp::Structure* get_io_struct(){return io_struct;}
  inline io::exp::Exporter* get_io_exporter(){return io_exporter;}

private:
  //Dependancy
  eng::Node* node_engine;
  vk::Node* node_vulkan;
  dat::Node* node_data;
  dyn::Node* node_dynamic;
  io::imp::Node* node_importer;

  //Child
  io::exp::Structure* io_struct;
  io::exp::Exporter* io_exporter;
  io::exp::gui::Panel* gui_export;
};

}
