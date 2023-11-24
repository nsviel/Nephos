#ifndef CAP_RECORD_H
#define CAP_RECORD_H

#include <GUI_base/BASE_panel.h>
#include <UTL_specific/common.h>
#include <UTL_capture/UTL_kinect/K4A_device/K4A_device.h>

class Kinect;


class KIN_recorder
{
public:
  //Constructor / Destructor
  KIN_recorder(Kinect* kinect);
  ~KIN_recorder();

  //Main function
  void kinect_recorder();

private:
  Kinect* kinect;
};

#endif
