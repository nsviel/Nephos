#pragma once

#include <Utility/Base/Class/Node.h>

namespace dyn::sen{class Node;}
namespace dat{class Node;}
namespace io{class Node;}

namespace vld{class Structure;}
namespace vld::main{class Capture;}
namespace vld::main{class Playback;}
namespace vld::gui{class Panel;}


namespace vld{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(dyn::sen::Node* node_sensor);
  ~Node();

public:
  //Main function
  void config();
  void init();
  void gui();
  void clean();

  inline dat::Node* get_node_data(){return node_data;}

  inline vld::Structure* get_vld_struct(){return vld_struct;}

private:
  dat::Node* node_data;
  io::Node* node_io;

  vld::main::Capture* vld_capture;
  vld::main::Playback* vld_playback;
  vld::Structure* vld_struct;
  vld::gui::Panel* gui_panel;
};

}
