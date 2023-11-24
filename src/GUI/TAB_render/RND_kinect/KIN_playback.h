#ifndef KIN_PLAYBACK_H
#define KIN_PLAYBACK_H

#include <GUI_base/BASE_panel.h>
#include <UTL_specific/common.h>

class Kinect;


class KIN_playback
{
public:
  //Constructor / Destructor
  KIN_playback();
  ~KIN_playback();

  //Main function

private:
  Kinect* kinect;
};

#endif
