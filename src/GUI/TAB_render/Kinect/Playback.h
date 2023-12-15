#pragma once

#include <GUI/GUI_utility/Base/Namespace.h>
#include <Utility/Specific/common.h>
#include <Engine/Capture/Kinect/Namespace.h>

class K4A_swarm;


namespace gui::kinect{

class Playback
{
public:
  //Constructor / Destructor
  Playback(eng::kinect::Kinect* kinect);
  ~Playback();

  //Main function
  void kinect_playback();

  //Subfunction
  void show_info();
  void show_info_device();
  void show_info_color();
  void show_info_depth();
  void show_info_synch();

private:
  eng::kinect::Kinect* kinect;
  K4A_swarm* k4a_swarm;
};

}
