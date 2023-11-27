#ifndef KIN_PLAYBACK_H
#define KIN_PLAYBACK_H

#include <GUI_base/BASE_panel.h>
#include <UTL_specific/common.h>

class Kinect;


class KIN_playback
{
public:
  //Constructor / Destructor
  KIN_playback(Kinect* kinect);
  ~KIN_playback();

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
  Kinect* kinect;
};

#endif
