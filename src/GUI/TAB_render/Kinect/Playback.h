#pragma once

#include <GUI/GUI_utility/Base/Namespace.h>
#include <Utility/Specific/common.h>
#include <Utility/Capture/UTL_kinect/Namespace.h>


namespace gui::kinect{

class Playback
{
public:
  //Constructor / Destructor
  Playback(util::kinect::Kinect* kinect);
  ~Playback();

  //Main function
  void kinect_playback();

  //Subfunction
  void show_player();
  void show_info_file();
  void show_info_recording();
  void show_info_stream();
  void show_info_synchro();
  void show_info_device();

private:
  util::kinect::Kinect* kinect;
};

}
