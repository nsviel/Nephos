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

  this->io_capture = node_importer->get_io_capture();
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

  const char* serial_ptr = udev_device_get_sysattr_value(usb_struct->udev.device, "serial");
  const char* node_ptr = udev_device_get_devnode(usb_struct->udev.device);

  if (serial_ptr && node_ptr){
    std::string serial = std::string(serial_ptr);
    std::string node = std::string(node_ptr);

    //usb_struct->map_device[node] = serial;
  }

  //---------------------------
}
void Attach::run_capture(){
  //---------------------------

  const char* vendor_ptr = udev_device_get_sysattr_value(usb_struct->udev.device, "idVendor");
  const char* product_ptr = udev_device_get_sysattr_value(usb_struct->udev.device, "idProduct");
  const char* serial_ptr = udev_device_get_sysattr_value(usb_struct->udev.device, "serial");
  const char* node_ptr = udev_device_get_devnode(usb_struct->udev.device);

  if (vendor_ptr && product_ptr && serial_ptr && node_ptr){
    std::string vendor = std::string(vendor_ptr);
    std::string product = std::string(product_ptr);
    std::string serial = std::string(serial_ptr);
    std::string node = std::string(node_ptr);

    std::shared_ptr<dat::base::Sensor> sensor = io_capture->run_capture(vendor, product);

    if(sensor){
      usb_struct->map_device[node] = sensor;
    }
  }

  //---------------------------
}

}
