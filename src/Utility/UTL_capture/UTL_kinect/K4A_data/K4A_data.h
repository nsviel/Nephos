#ifndef K4A_DATA_H
#define K4A_DATA_H

#include <UTL_capture/UTL_kinect/K4A_struct/Struct_k4a_device.h>

#include <UTL_specific/common.h>
#include <k4a/k4a.h>
#include <k4a/k4a.hpp>

class Struct_kinect;


class K4A_data
{
public:
  //Constructor / Destructor
  K4A_data(Struct_kinect* struct_kinect);
  ~K4A_data();

public:
  //Main function
  void find_data_from_capture(Struct_k4a_data* data, k4a::capture capture);

private:
  Struct_kinect* struct_kinect;
};

#endif
