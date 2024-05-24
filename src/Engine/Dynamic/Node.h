#pragma once

#include <Utility/Base/Type/Node.h>

namespace eng{class Node;}
namespace dat{class Node;}
namespace eng{class Node;}
namespace dyn::gui{class Player;}
namespace dyn::gui{class Stream;}


namespace dyn{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(eng::Node* node_engine);
  ~Node();

public:
  void init();
  void loop();
  void clean();
  void gui();
  void reset();

  inline eng::Node* get_node_engine(){return node_engine;}
  inline dat::Node* get_node_data(){return node_data;}
  inline dyn::gui::Player* get_gui_player(){return gui_player;}

private:
  eng::Node* node_engine;
  dat::Node* node_data;

  dyn::gui::Player* gui_player;
  dyn::gui::Stream* gui_stream;
};

}
