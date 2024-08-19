#pragma once

#include <Utility/Base/Class/Node.h>

namespace dat{class Node;}
namespace dat::elm{class Node;}
namespace dat::atr{class Structure;}
namespace dat::atr::gui{class Panel;}


namespace dat::atr{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(dat::Node* node_data);
  ~Node();

public:
  inline dat::elm::Node* get_node_element(){return node_element;}
  inline dat::atr::Structure* get_atr_struct(){return atr_struct;}
  inline dat::atr::gui::Panel* get_gui_panel(){return gui_panel;}

private:
  dat::elm::Node* node_element;
  dat::atr::Structure* atr_struct;
  dat::atr::gui::Panel* gui_panel;
};

}
