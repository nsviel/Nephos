#include "Attach.h"

#include <USB/Namespace.h>
#include <IO/Namespace.h>
#include <Utility/Namespace.h>
#include <thread>


namespace usb{

//Constructor / Destructor
Attach::Attach(usb::Node* node_usb){
  //---------------------------

  io::Node* node_io = node_usb->get_node_io();
  io::imp::Node* node_importer = node_io->get_node_importer();

  this->io_importer = node_importer->get_io_importer();
  this->usb_struct = node_usb->get_usb_struct();

  //---------------------------
}
Attach::~Attach(){}

//Main function
void Attach::manage_action(){
  //---------------------------

  this->update_device_map();
  this->run_capture();

  //---------------------------
}

//Subfunction
void Attach::update_device_map(){
  //---------------------------

  std::string serial = std::string(udev_device_get_sysattr_value(usb_struct->udev.device, "serial"));
  std::string node = std::string(udev_device_get_devnode(usb_struct->udev.device));

  usb_struct->map_device[node] = serial;

  //---------------------------
}
void Attach::run_capture(){
  //---------------------------

  std::string vendor = std::string(udev_device_get_sysattr_value(usb_struct->udev.device, "idVendor"));
  std::string product = std::string(udev_device_get_sysattr_value(usb_struct->udev.device, "idProduct"));

  io::base::Importer* importer = io_importer->obtain_importer(vendor, product);
  if(importer == nullptr) return;

  say(importer->reference.name);
  say("plug");


  //---------------------------
}

}
