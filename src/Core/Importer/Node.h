#pragma once

#include <Utility/Base/Class/Node.h>

namespace vk{class Node;}
namespace dat{class Node;}
namespace eng{class Node;}
namespace dyn{class Node;}
namespace io{class Structure;}
namespace io{class Importer;}
namespace io::imp{class Operation;}
namespace io{class Exporter;}
namespace io{class Transformation;}
namespace io::imp::bookmark{class Manager;}
namespace io::imp::gui{class Panel;}
namespace io::gui::exporter{class Panel;}
namespace io::gui::transformation{class Panel;}


namespace io::imp{

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

  inline io::imp::Structure* get_io_struct(){return io_struct;}
  inline io::Importer* get_io_importer(){return io_importer;}
  inline io::importer::Operation* get_imp_operation(){return io_import_ope;}
  inline io::bookmark::Manager* get_io_bookmark(){return io_bookmark;}

private:
  //Dependancy
  eng::Node* node_engine;
  vk::Node* node_vulkan;
  dat::Node* node_data;
  dyn::Node* node_dynamic;

  //Child
  io::Structure* io_struct;
  io::Importer* io_importer;
  io::importer::Operation* io_import_ope;
  io::Exporter* io_exporter;
  io::Transformation* io_transformation;
  io::bookmark::Manager* io_bookmark;
  io::gui::importer::Panel* gui_import;
  io::gui::exporter::Panel* gui_export;
  io::gui::transformation::Panel* gui_transformation;

  bool show_scene = true;
  bool show_loader = true;
};

}
