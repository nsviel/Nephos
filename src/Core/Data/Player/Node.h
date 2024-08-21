#pragma once

#include <Utility/Base/Class/Node.h>

namespace dat{class Node;}
namespace dat::atr{class Node;}
namespace dat::gph{class Node;}

namespace dat::ply{class Player;}
namespace dat::ply::gui{class Panel;}


namespace dat::ply{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(dat::Node* node_data);
  ~Node();

public:
  //Main function
  void loop();
  void gui();
  void reset();

  inline dat::atr::Node* get_node_attribut(){return node_attribut;}
  inline dat::gph::Node* get_node_graph(){return node_graph;}

  inline dat::ply::Player* get_dyn_player(){return dyn_player;}
  inline dat::ply::gui::Panel* get_gui_player(){return gui_player;}

private:
  dat::atr::Node* node_attribut;
  dat::gph::Node* node_graph;

  dat::ply::Player* dyn_player;
  dat::ply::gui::Panel* gui_player;
};

}
