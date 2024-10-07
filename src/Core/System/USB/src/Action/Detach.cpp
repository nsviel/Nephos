#include "Detach.h"

#include <USB/Namespace.h>
#include <Data/Namespace.h>
#include <Utility/Namespace.h>
#include <thread>


namespace usb{

//Constructor / Destructor
Detach::Detach(usb::Node* node_usb){
  //---------------------------

  dat::Node* node_data = node_usb->get_node_data();
  dat::gph::Node* node_graph = node_data->get_node_graph();

  this->usb_struct = node_usb->get_usb_struct();
  this->dat_element = node_graph->get_gph_element();

  //---------------------------
}
Detach::~Detach(){}

//Main function
void Detach::manage_action(){
  //---------------------------

  const char* node_ptr = udev_device_get_devnode(usb_struct->udev.device);

  if(node_ptr){
    std::string node = std::string(node_ptr);

    auto it = usb_struct->map_device.find(node);
    if(it != usb_struct->map_device.end()){
            say("unplug");
      std::shared_ptr<dat::base::Sensor> sensor = usb_struct->map_device[node];
      dat_element->remove_entity(sensor);
      say("unplug");
    }

  }

  //---------------------------
}

}
