#include "Device.h"

#include <USB/Namespace.h>
#include <Utility/Namespace.h>
#include <thread>


namespace usb{

//Constructor / Destructor
Device::Device(usb::Node* node_usb){
  //---------------------------

  this->usb_struct = node_usb->get_usb_struct();

  //---------------------------
}
Device::~Device(){}

//Main function
void Device::init() {
  //---------------------------

  //RealSense D455
  usb::structure::Device d455;
  d455.name = "Intel RealSense Depth Camera 455";
  d455.vendor = "8086";
  d455.product = "0b5c";
  usb_struct->vec_device.push_back(d455);

  //Kinect azur
  usb::structure::Device kinect;
  kinect.name = "Kinect Azure Depth Camera";
  kinect.vendor = "045e";
  kinect.product = "097b";
  usb_struct->vec_device.push_back(kinect);

  //---------------------------
}

}
