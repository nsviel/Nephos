#pragma once

#include <Utility/Specific/Common.h>

namespace eng{class Node;}
namespace eng::scene{class Node;}
namespace eng::capture{class Node;}
namespace velodyne::gui{class Player;}
namespace velodyne::structure{class Velodyne;}


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

  inline velodyne::structure::Velodyne* get_velo_struct(){return velo_struct;}

private:
  eng::Node* node_engine;
  eng::scene::Node* node_scene;
  velodyne::gui::Player* gui_player;
  velodyne::structure::Velodyne* velo_struct;
};

}
