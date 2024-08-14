#pragma once

#include <Utility/Base/Class/Node.h>

namespace vk{class Node;}
namespace dat{class Node;}
namespace eng{class Node;}
namespace dyn{class Node;}
namespace io{class Structure;}
namespace io{class Exporter;}
namespace io{class Transformation;}
namespace io::gui::exporter{class Panel;}
namespace io::gui::transformation{class Panel;}


namespace io{

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

  inline io::Structure* get_io_struct(){return io_struct;}
  inline io::Exporter* get_io_exporter(){return io_exporter;}
  inline io::Transformation* get_io_transformation(){return io_transformation;}

private:
  //Dependancy
  eng::Node* node_engine;
  vk::Node* node_vulkan;
  dat::Node* node_data;
  dyn::Node* node_dynamic;

  //Child
  io::Structure* io_struct;
  io::Exporter* io_exporter;
  io::Transformation* io_transformation;
  io::gui::exporter::Panel* gui_export;
  io::gui::transformation::Panel* gui_transformation;
};

}
