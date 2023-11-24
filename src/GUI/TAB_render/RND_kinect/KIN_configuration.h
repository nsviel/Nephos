#ifndef KIN_CONFIGURATION_H
#define KIN_CONFIGURATION_H

#include <UTL_specific/common.h>


class KIN_configuration
{
public:
  //Constructor / Destructor
  KIN_configuration();
  ~KIN_configuration();

  //Main function
  void kinect_devices();
  void configuration_device();
  void configuration_depth();
  void configuration_color();
  void configuration_general();
  void firmware_info();
  
private:
};

#endif
