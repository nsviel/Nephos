#ifndef CAP_RECORD_H
#define CAP_RECORD_H

#include <GUI_base/BASE_panel.h>
#include <UTL_specific/common.h>
#include <UTL_capture/UTL_kinect/K4A_device/K4A_device.h>

class GUI;


class KIN_recorder : public BASE_panel
{
public:
  //Constructor / Destructor
  KIN_recorder(GUI* gui, bool* show_window, string name);
  ~KIN_recorder();

  //Main function
  void design_panel();

  //Subfunction
  void record_parameter();

private:
};

#endif
