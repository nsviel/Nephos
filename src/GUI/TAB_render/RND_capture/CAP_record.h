#ifndef CAP_RECORD_H
#define CAP_RECORD_H

#include <GUI_base/BASE_panel.h>
#include <UTL_specific/common.h>
#include <UTL_capture/UTL_kinect/K4A_device/K4A_device.h>

class GUI;


class CAP_record : public BASE_panel
{
public:
  //Constructor / Destructor
  CAP_record(GUI* gui, bool* show_window, string name);
  ~CAP_record();

  //Main function
  void design_panel();

  //Subfunction
  void record_parameter();

private:
};

#endif
