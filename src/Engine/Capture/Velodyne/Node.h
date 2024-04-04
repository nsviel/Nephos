#pragma once

#include <Utility/Specific/Common.h>

namespace eng{class Node;}
namespace eng::scene{class Node;}
namespace eng::capture{class Node;}
namespace vld::processing{class Player;}
namespace vld::structure{class Main;}
namespace vld::thread{class Server;}
namespace vld::gui{class Velodyne;}


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
  void clean();

  inline vld::structure::Main* get_vld_struct(){return vld_struct;}

private:
  eng::Node* node_engine;
  eng::scene::Node* node_scene;
  vld::gui::Velodyne* gui_velodyne;
  vld::structure::Main* vld_struct;
  vld::processing::Player* vld_player;
  vld::thread::Server* vld_server;
};

}
