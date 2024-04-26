#pragma once

#include <Utility/Specific/Common.h>

namespace eng{class Node;}
namespace eng::scene{class Node;}
namespace eng::capture{class Node;}
namespace vld::main{class Capture;}
namespace vld::main{class Playback;}
namespace vld::structure{class Main;}
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

  inline eng::Node* get_node_engine(){return node_engine;}
  inline eng::scene::Node* get_node_scene(){return node_scene;}
  inline vld::structure::Main* get_vld_struct(){return vld_struct;}

private:
  eng::Node* node_engine;
  eng::scene::Node* node_scene;

  vld::main::Capture* vld_capture;
  vld::main::Playback* vld_playback;
  vld::gui::Velodyne* gui_velodyne;
  vld::structure::Main* vld_struct;
};

}