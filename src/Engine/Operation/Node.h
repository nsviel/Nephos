#pragma once

#include <Utility/Base/Class/Node.h>

namespace eng{class Node;}
namespace ope{class Structure;}
namespace ope::gui{class Panel;}


namespace ope{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(eng::Node* node_engine);
  ~Node();

public:
  //Main function


  //Subfunction

  inline eng::Node* get_node_engine(){return node_engine;}
  inline ope::Structure* get_ope_struct(){return ope_struct;}
  inline ope::gui::Panel* get_gui_panel(){return gui_panel;}

private:
  eng::Node* node_engine;
  ope::Structure* ope_struct;
  ope::gui::Panel* gui_panel;
};

}
