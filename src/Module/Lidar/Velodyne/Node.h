#pragma once

#include <Utility/Specific/Common.h>

namespace ldr{class Node;}
namespace dat{class Node;}
namespace eng{class Node;}
namespace vld::main{class Capture;}
namespace vld::main{class Playback;}
namespace vld::structure{class Main;}
namespace vld::gui{class Velodyne;}


namespace vld{

class Node : public utl::type::Node
{
public:
  //Constructor / Destructor
  Node(eng::Node* node_engine);
  ~Node();

public:
  //Main function
  void config();
  void init();
  void gui();
  void clean();

  inline dat::Node* get_node_data(){return node_data;}
  inline eng::Node* get_node_engine(){return node_engine;}
  inline vld::structure::Main* get_vld_struct(){return vld_struct;}

private:
  eng::Node* node_engine;
  dat::Node* node_data;
  ldr::Node* node_loader;

  vld::main::Capture* vld_capture;
  vld::main::Playback* vld_playback;
  vld::gui::Velodyne* gui_velodyne;
  vld::structure::Main* vld_struct;
};

}
