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
  void show_file_information();

private:
  Kinect* kinect;
};

#endif
