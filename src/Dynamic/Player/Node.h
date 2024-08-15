#pragma once

#include <Utility/Base/Class/Node.h>

namespace core{class Node;}
namespace dat{class Node;}
namespace core{class Node;}
namespace rad{class Node;}
namespace prf{class Node;}
namespace ope{class Node;}
namespace dyn{class Structure;}
namespace dyn::ply{class Player;}
namespace dyn::ply::gui{class Panel;}
namespace dyn::gui::stream{class Panel;}


namespace dyn::ply{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(core::Node* node_core);
  ~Node();

public:
  void loop();
  void gui();
  void reset();

  inline core::Node* get_node_core(){return node_core;}
  inline dat::Node* get_node_data(){return node_data;}
  inline rad::Node* get_node_radio(){return node_radio;}
  inline prf::Node* get_node_profiler(){return node_profiler;}
  inline ope::Node* get_node_operation(){return node_operation;}

  inline dyn::ply::Player* get_dyn_player(){return dyn_player;}
  inline dyn::ply::gui::Panel* get_gui_player(){return gui_player;}

private:
  core::Node* node_core;
  dat::Node* node_data;
  rad::Node* node_radio;
  prf::Node* node_profiler;
  ope::Node* node_operation;

  dyn::ply::Player* dyn_player;
  dyn::ply::gui::Panel* gui_player;
  dyn::gui::stream::Panel* gui_stream;
};

}
