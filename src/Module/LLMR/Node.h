#pragma once

#include <Utility/Base/Class/Node.h>

namespace mod{class Node;}
namespace core{class Node;}
namespace dat{class Node;}

namespace llmr{class Interface;}
namespace llmr::gui{class Panel;}


namespace llmr{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(mod::Node* node_module);
  ~Node();

public:
  //Main function
  void init();
  void gui();

  inline core::Node* get_node_core(){return node_core;}
  inline dat::Node* get_node_data(){return node_data;}
  inline llmr::Interface* get_llmr_interface(){return llmr_interface;}

private:
  //Dependancy
  core::Node* node_core;
  dat::Node* node_data;

  //Child
  llmr::Interface* llmr_interface;
  llmr::gui::Panel* gui_panel;
};

}
