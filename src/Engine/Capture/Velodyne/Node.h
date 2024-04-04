#pragma once

#include <Utility/Specific/Common.h>

namespace eng{class Node;}
namespace eng::scene{class Node;}
namespace eng::capture{class Node;}
namespace vld::gui{class Player;}
namespace vld::structure{class Main;}


namespace vld{

class Node : public utl::type::Node
{
public:
  //Constructor / Destructor
  Node(eng::capture::Node* node_capture);
  ~Node();

public:
  //Main function
  void config();
  void init();
  void gui();

  inline vld::structure::Main* get_vld_struct(){return vld_struct;}

private:
  eng::Node* node_engine;
  eng::scene::Node* node_scene;
  vld::gui::Player* gui_player;
  vld::structure::Main* vld_struct;
};

}
