#pragma once

#include <Utility/Base/Class/Node.h>

namespace dat{class Node;}
namespace dat::atr{class Structure;}
namespace dat::atr::gui{class Panel;}
namespace dat::gph{class Node;}


namespace dat::atr{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(dat::Node* node_data);
  ~Node();

public:
  inline dat::gph::Node* get_node_graph(){return node_graph;}
  inline dat::atr::Structure* get_atr_struct(){return atr_struct;}

private:
  dat::gph::Node* node_graph;

  dat::atr::Structure* atr_struct;
  dat::atr::gui::Panel* gui_attribut;
};

}
