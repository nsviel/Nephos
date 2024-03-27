#pragma once

#include <Utility/Specific/Common.h>

namespace k4n{class Node;}
namespace k4n::dev{class Master;}
namespace k4n::dev{class Swarm;}
namespace k4n::gui{class Capture;}
namespace k4n::gui{class Playback;}


namespace k4n::gui{

class Master
{
public:
  //Constructor / Destructor
  Master(k4n::Node* node_k4n);
  ~Master();

  //Main function
  void show_master_info(k4n::dev::Master* master);

  //Subfunction
  void show_info(k4n::dev::Master* master);
  void show_operation(k4n::dev::Master* master);

  //Processing function
  void show_transformation(k4n::dev::Master* master);
  void show_colorization(k4n::dev::Master* master);
  void show_possible_ope(k4n::dev::Master* master);
  void show_voxelization(k4n::dev::Master* master);
  void show_normal(k4n::dev::Master* master);
  void show_recorder(k4n::dev::Master* master);

private:
  k4n::Node* node_k4n;
  k4n::dev::Swarm* k4n_swarm;
  k4n::gui::Capture* gui_capture;
  k4n::gui::Playback* gui_playback;

  int item_width;
};

}
