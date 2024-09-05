#include "Monitor.h"

#include <USB/Namespace.h>
#include <Utility/Namespace.h>
#include <thread>


namespace usb{

//Constructor / Destructor
Monitor::Monitor(usb::Node* node_usb){
  //---------------------------

  this->usb_struct = node_usb->get_usb_struct();
  this->usb_attach = new usb::Attach(node_usb);
  this->usb_detach = new usb::Detach(node_usb);

  //---------------------------
}
Monitor::~Monitor(){}

//Main function
void Monitor::init(){
  //---------------------------

  //Contexte
  usb_struct->udev.contexte = udev_new();
  if (!usb_struct->udev.contexte){
    std::cerr << "Can't create udev\n";
    return;
  }

  //USB listener
  usb_struct->udev.monitor = udev_monitor_new_from_netlink(usb_struct->udev.contexte, "udev");

  //Add filter
  udev_monitor_filter_add_match_subsystem_devtype(usb_struct->udev.monitor, "usb", "usb_device");

  //Enable monitor to receive events
  udev_monitor_enable_receiving(usb_struct->udev.monitor);

  //Get file descriptor
  usb_struct->udev.fd = udev_monitor_get_fd(usb_struct->udev.monitor);

  this->manage_init_state();

  // Create and run the thread
  std::thread monitor_thread(&Monitor::loop, this);
  monitor_thread.detach();

  //---------------------------
}
void Monitor::loop(){
  //---------------------------

  while (true){
    //Prepare file descriptor
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(usb_struct->udev.fd, &fds);

    // Wait for an event on the file descriptor
    int ret = select(usb_struct->udev.fd + 1, &fds, NULL, NULL, NULL);
    int event = FD_ISSET(usb_struct->udev.fd, &fds);

    //Even occur
    if (ret > 0 && event){
      this->manage_event();
    }
  }

  //---------------------------
}
void Monitor::close(){
  //---------------------------

  udev_monitor_unref(usb_struct->udev.monitor);
  udev_unref(usb_struct->udev.contexte);

  //---------------------------
}

//Subfunction
void Monitor::manage_init_state(){
  //---------------------------

  struct udev_enumerate* enumerate = udev_enumerate_new(usb_struct->udev.contexte);
  udev_enumerate_add_match_subsystem(enumerate, "usb");
  udev_enumerate_scan_devices(enumerate);

  struct udev_list_entry* devices = udev_enumerate_get_list_entry(enumerate);
  struct udev_list_entry* entry;

  udev_list_entry_foreach(entry, devices){
    const char* path = udev_list_entry_get_name(entry);
    struct udev_device* dev = udev_device_new_from_syspath(usb_struct->udev.contexte, path);

    // Handle device as if it was "added" just now
    usb_struct->udev.device = dev;
    usb_attach->manage_action();  // You may need to customize this to suit your needs

    // Release the device reference
    udev_device_unref(dev);
  }

  udev_enumerate_unref(enumerate);

  //---------------------------
}
void Monitor::manage_event(){
  //---------------------------

  //Event associated device
  usb_struct->udev.device = udev_monitor_receive_device(usb_struct->udev.monitor);
  if (!usb_struct->udev.device) return;

  //Event action
  std::string action = std::string(udev_device_get_action(usb_struct->udev.device));
  if(action == "add"){
    usb_attach->manage_action();
  }
  else if(action == "remove"){
    usb_detach->manage_action();
  }else{

  }

  //Release device
  udev_device_unref(usb_struct->udev.device);

  //---------------------------
}

}
