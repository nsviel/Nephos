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
  void show_player();
  void show_file();
  void show_recording();
  void show_stream();
  void show_synchro();
  void show_device();

private:
  eng::kinect::Kinect* kinect;
  K4A_swarm* k4a_swarm;
};

}
