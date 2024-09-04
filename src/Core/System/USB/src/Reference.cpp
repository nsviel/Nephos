#include "Reference.h"

#include <USB/Namespace.h>
#include <Utility/Namespace.h>
#include <thread>


namespace usb{

//Constructor / Destructor
Reference::Reference(usb::Node* node_usb){
  //---------------------------

  this->usb_struct = node_usb->get_usb_struct();

  //---------------------------
}
Reference::~Reference(){}

//Main function
void Reference::init() {
  //---------------------------

  //RealSense D455
  usb::structure::Reference d455;
  d455.name = "Intel RealSense Depth Camera 455";
  d455.vendor = "8086";
  d455.product = "0b5c";
  usb_struct->vec_reference.push_back(d455);

  //Kinect azur
  usb::structure::Reference kinect;
  kinect.name = "Kinect Azure Depth Camera";
  kinect.vendor = "045e";
  kinect.product = "097b";
  usb_struct->vec_reference.push_back(kinect);

  //---------------------------
}

}
