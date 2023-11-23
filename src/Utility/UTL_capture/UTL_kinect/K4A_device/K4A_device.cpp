#include "K4A_device.h"

#include <UTL_capture/UTL_kinect/Struct_kinect.h>


//Constructor / Destructor
K4A_device::K4A_device(Struct_kinect* struct_kinect){
  //---------------------------

  this->struct_kinect = struct_kinect;

  //---------------------------
}
K4A_device::~K4A_device(){}

//Main function
void K4A_device::refresh_device_list(){
  //---------------------------

  struct_kinect->vec_device.clear();

  const uint32_t nb_device = k4a_device_get_installed_count();
  for(int i=0; i<nb_device; i++){
    try{
      k4a::device device = k4a::device::open(i);

      Struct_k4a_device struct_device;
      struct_device.index = i;
      struct_device.serial_number = device.get_serialnum();
      struct_kinect->vec_device.push_back(struct_device);
    }
    catch(const int error){
      cout<<"[error] refresh device vector"<<endl;
      continue;
    }
  }

  //Default selection
  if(nb_device > 0){
    struct_kinect->selected_device = &struct_kinect->vec_device[0];
  }

  //---------------------------
}
string K4A_device::find_name_from_config(k4a_wired_sync_mode_t& value){
  string name = "";
  //---------------------------

  switch (value){
    case K4A_WIRED_SYNC_MODE_STANDALONE:{
      name = "K4A_WIRED_SYNC_MODE_STANDALONE";
      break;
    }
    case K4A_WIRED_SYNC_MODE_MASTER:{
      name = "K4A_WIRED_SYNC_MODE_MASTER";
      break;
    }
    case K4A_WIRED_SYNC_MODE_SUBORDINATE:{
      name = "K4A_WIRED_SYNC_MODE_SUBORDINATE";
      break;
    }
    default:{
      cout<<"[error] Unrecognized sync mode"<<endl;
    }
  }

  //---------------------------
  return name;
}
string K4A_device::find_name_from_config(k4a_fps_t& value){
  string name = "";
  //---------------------------

  switch (value){
    case K4A_FRAMES_PER_SECOND_5:{
      name = "K4A_FRAMES_PER_SECOND_5";
      break;
    }
    case K4A_FRAMES_PER_SECOND_15:{
      name = "K4A_FRAMES_PER_SECOND_15";
      break;
    }
    case K4A_FRAMES_PER_SECOND_30:{
      name = "K4A_FRAMES_PER_SECOND_30";
      break;
    }
    default:{
      cout<<"[error] Unrecognized fps"<<endl;
    }
  }

  //---------------------------
  return name;
}
string K4A_device::find_name_from_config(k4a_depth_mode_t& value){
  string name = "";
  //---------------------------

  switch (value){
    case K4A_DEPTH_MODE_OFF:{
      name = "K4A_DEPTH_MODE_OFF";
      break;
    }
    case K4A_DEPTH_MODE_NFOV_2X2BINNED:{
      name = "K4A_DEPTH_MODE_NFOV_2X2BINNED";
      break;
    }
    case K4A_DEPTH_MODE_NFOV_UNBINNED:{
      name = "K4A_DEPTH_MODE_NFOV_UNBINNED";
      break;
    }
    case K4A_DEPTH_MODE_WFOV_2X2BINNED:{
      name = "K4A_DEPTH_MODE_WFOV_2X2BINNED";
      break;
    }
    case K4A_DEPTH_MODE_WFOV_UNBINNED:{
      name = "K4A_DEPTH_MODE_WFOV_UNBINNED";
      break;
    }
    case K4A_DEPTH_MODE_PASSIVE_IR:{
      name = "K4A_DEPTH_MODE_PASSIVE_IR";
      break;
    }
    default:{
      cout<<"[error] Unrecognized depth mode"<<endl;
    }
  }

  //---------------------------
  return name;
}
string K4A_device::find_name_from_config(k4a_color_resolution_t& value){
  string name = "";
  //---------------------------

  switch (value){
    case K4A_COLOR_RESOLUTION_OFF:{
      name = "K4A_COLOR_RESOLUTION_OFF";
      break;
    }
    case K4A_COLOR_RESOLUTION_720P:{
      name = "K4A_COLOR_RESOLUTION_720P";
      break;
    }
    case K4A_COLOR_RESOLUTION_1080P:{
      name = "K4A_COLOR_RESOLUTION_1080P";
      break;
    }
    case K4A_COLOR_RESOLUTION_1440P:{
      name = "K4A_COLOR_RESOLUTION_1440P";
      break;
    }
    case K4A_COLOR_RESOLUTION_1536P:{
      name = "K4A_COLOR_RESOLUTION_1536P";
      break;
    }
    case K4A_COLOR_RESOLUTION_2160P:{
      name = "K4A_COLOR_RESOLUTION_2160P";
      break;
    }
    case K4A_COLOR_RESOLUTION_3072P:{
      name = "K4A_COLOR_RESOLUTION_3072P";
      break;
    }
    default:{
      cout<<"[error] Unrecognized color resolution"<<endl;
    }
  }

  //---------------------------
  return name;
}
string K4A_device::find_name_from_config(k4a_image_format_t& value){
  string name = "";
  //---------------------------

  switch (value){
    case K4A_IMAGE_FORMAT_COLOR_MJPG:{
      name = "K4A_IMAGE_FORMAT_COLOR_MJPG";
      break;
    }
    case K4A_IMAGE_FORMAT_COLOR_NV12:{
      name = "K4A_IMAGE_FORMAT_COLOR_NV12";
      break;
    }
    case K4A_IMAGE_FORMAT_COLOR_YUY2:{
      name = "K4A_IMAGE_FORMAT_COLOR_YUY2";
      break;
    }
    case K4A_IMAGE_FORMAT_COLOR_BGRA32:{
      name = "K4A_IMAGE_FORMAT_COLOR_BGRA32";
      break;
    }
    case K4A_IMAGE_FORMAT_DEPTH16:{
      name = "K4A_IMAGE_FORMAT_DEPTH16";
      break;
    }
    case K4A_IMAGE_FORMAT_IR16:{
      name = "K4A_IMAGE_FORMAT_IR16";
      break;
    }
    case K4A_IMAGE_FORMAT_CUSTOM:{
      name = "K4A_IMAGE_FORMAT_CUSTOM";
      break;
    }
    default:{
      cout<<"[error] Unrecognized image format"<<endl;
    }
  }

  //---------------------------
  return name;
}
