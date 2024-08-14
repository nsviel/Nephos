#pragma once

#include <Utility/Base/Class/Node.h>

namespace vk{class Node;}
namespace dat{class Node;}
namespace eng{class Node;}
namespace dyn{class Node;}
namespace io::imp{class Structure;}
namespace io::imp{class Importer;}
namespace io::imp{class Operation;}
namespace io::imp{class Bookmark;}
namespace io::imp::gui{class Panel;}


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
  inline io::imp::Importer* get_io_importer(){return io_importer;}
  inline io::imp::Operation* get_imp_operation(){return io_import_ope;}
  inline io::imp::Bookmark* get_io_bookmark(){return io_bookmark;}

private:
  //Dependancy
  eng::Node* node_engine;
  vk::Node* node_vulkan;
  dat::Node* node_data;
  dyn::Node* node_dynamic;

  //Child
  io::imp::Structure* io_struct;
  io::imp::Importer* io_importer;
  io::imp::Operation* io_import_ope;
  io::imp::Bookmark* io_bookmark;
  io::imp::gui::Panel* gui_import;
};

}
