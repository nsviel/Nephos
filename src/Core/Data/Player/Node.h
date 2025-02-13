#pragma once

#include <Utility/Base/Class/Node.h>

namespace dat{class Node;}
namespace dat::atr{class Node;}
namespace dat::gph{class Node;}

namespace dat::ply{class Structure;}
namespace dat::ply{class State;}
namespace dat::ply{class Button;}
namespace dat::ply{class Subscriber;}
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

  inline dat::ply::Structure* get_ply_struct(){return ply_struct;}
  inline dat::ply::State* get_ply_state(){return ply_state;}
  inline dat::ply::Button* get_ply_button(){return ply_button;}
  inline dat::ply::gui::Panel* get_gui_player(){return gui_player;}

private:
  dat::atr::Node* node_attribut;
  dat::gph::Node* node_graph;

  dat::ply::Structure* ply_struct;
  dat::ply::State* ply_state;
  dat::ply::Button* ply_button;
  dat::ply::Subscriber* ply_subscriber;
  dat::ply::gui::Panel* gui_player;
};

}
