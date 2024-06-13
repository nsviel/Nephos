#pragma once

#include <Utility/Base/Type/Node.h>

namespace vk{class Node;}
namespace dat{class Node;}
namespace eng{class Node;}
namespace dyn{class Node;}
namespace ldr{class Structure;}
namespace ldr::io{class Importer;}
namespace ldr::importer{class Operation;}
namespace ldr::exporter{class Operation;}
namespace ldr::io{class Exporter;}
namespace ldr::bookmark{class Manager;}
namespace ldr::gui::importer{class Panel;}
namespace ldr::gui::exporter{class Panel;}


namespace ldr{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(eng::Node* node_engine);
  ~Node();

public:
  void init();
  void loop();
  void clean();
  void gui();
  void reset();

  inline eng::Node* get_node_engine(){return node_engine;}
  inline vk::Node* get_node_vulkan(){return node_vulkan;}
  inline dat::Node* get_node_data(){return node_data;}
  inline dyn::Node* get_node_dynamic(){return node_dynamic;}

  inline ldr::Structure* get_ldr_struct(){return ldr_struct;}
  inline ldr::io::Importer* get_ldr_importer(){return ldr_importer;}
  inline ldr::importer::Operation* get_ldr_import_ope(){return ldr_import_ope;}
  inline ldr::exporter::Operation* get_ldr_export_ope(){return ldr_export_ope;}
  inline ldr::io::Exporter* get_ldr_exporter(){return ldr_exporter;}
  inline ldr::bookmark::Manager* get_ldr_bookmark(){return ldr_bookmark;}

private:
  //Dependancy
  eng::Node* node_engine;
  vk::Node* node_vulkan;
  dat::Node* node_data;
  dyn::Node* node_dynamic;

  //Child
  ldr::Structure* ldr_struct;
  ldr::io::Importer* ldr_importer;
  ldr::importer::Operation* ldr_import_ope;
  ldr::exporter::Operation* ldr_export_ope;
  ldr::io::Exporter* ldr_exporter;
  ldr::bookmark::Manager* ldr_bookmark;
  ldr::gui::importer::Panel* gui_import;
  ldr::gui::exporter::Panel* gui_export;

  bool show_scene = true;
  bool show_loader = true;
};

}
