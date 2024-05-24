#pragma once

#include <Utility/Specific/Common.h>

namespace k4n{class Node;}
namespace k4n::dev{class Master;}
namespace k4n::gui{class Capture;}
namespace k4n::gui{class Playback;}


namespace k4n::gui{

class Player
{
public:
  //Constructor / Destructor
  Player(k4n::Node* node_k4n);
  ~Player();

  //Main function
  void show_info(k4n::dev::Master* master);
  void show_parameter(k4n::dev::Master* master);

  //Subfunction
  void show_transformation_mode(k4n::dev::Master* master);

private:
  k4n::Node* node_k4n;
  k4n::gui::Capture* gui_capture;
  k4n::gui::Playback* gui_playback;

  int item_width;
};

}
