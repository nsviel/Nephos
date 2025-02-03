#pragma once

#include <Utility/Base/Class/Node.h>

namespace mod{class Node;}
namespace core{class Node;}
namespace dat{class Node;}

namespace net::wsok{class Client;}
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

private:
  //Dependancy
  core::Node* node_core;
  dat::Node* node_data;

  //Child
  net::wsok::Client* llmr_wsok;
  llmr::gui::Panel* gui_panel;
};

}
