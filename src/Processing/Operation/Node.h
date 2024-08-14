#pragma once

#include <Utility/Base/Class/Node.h>

namespace core{class Node;}
namespace ope{class Structure;}
namespace ope::gui{class Panel;}


namespace ope{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(core::Node* node_core);
  ~Node();

public:
  //Main function


  //Subfunction

  inline core::Node* get_node_core(){return node_core;}
  inline ope::Structure* get_ope_struct(){return ope_struct;}
  inline ope::gui::Panel* get_gui_panel(){return gui_panel;}

private:
  core::Node* node_core;
  ope::Structure* ope_struct;
  ope::gui::Panel* gui_panel;
};

}
