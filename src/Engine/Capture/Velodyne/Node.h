#pragma once

#include <Utility/Specific/Common.h>

namespace eng{class Node;}
namespace eng::scene{class Node;}
namespace eng::capture{class Node;}
namespace velodyne::gui{class Player;}


namespace velodyne{

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

private:
  eng::Node* node_engine;
  eng::scene::Node* node_scene;
  velodyne::gui::Player* gui_player;
};

}
