#pragma once

#include <GUI/GUI_utility/Base/Namespace.h>
#include <Utility/Specific/common.h>
#include <Engine/Capture/K4N/Namespace.h>

class K4A_swarm;


namespace gui::kinect{

class Playback
{
public:
  //Constructor / Destructor
  Playback(k4n::Node* node_kinect);
  ~Playback();

  //Main function
  void kinect_playback();

  //Subfunction
  void show_info_device();
  void show_info_color();
  void show_info_depth();
  void show_info_synch();

private:
  k4n::Node* node_kinect;
  K4A_swarm* k4a_swarm;
};

}
