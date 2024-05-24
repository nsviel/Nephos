#include "Manager.h"

#include <Utility/Namespace.h>
#include <Radiometry/Namespace.h>


namespace rad::detection{

//Constructor / Destructor
Manager::Manager(rad::Node* node_radio){
  //---------------------------

  dat::Node* node_data = node_radio->get_node_data();

  this->dat_graph = node_data->get_dat_graph();
  this->rad_image_detection = new rad::detection::image::Detection(node_radio);
  this->rad_cloud_detection = new rad::detection::cloud::Detection(node_radio);
  this->map_step[rad::detection::cloud::WAIT_VALIDATION] = "Wait validation";
  this->map_step[rad::detection::cloud::PROCESSING] = "Detectioning";
  this->step = rad::detection::cloud::WAIT_VALIDATION;

  //---------------------------
}
Manager::~Manager(){}

//Main function
void Manager::loop(){
  dat::base::Entity* entity = dat_graph->get_selected_entity();
  //---------------------------

  if(dat::base::Sensor* sensor = dynamic_cast<dat::base::Sensor*>(entity)){
    //rad_image_detection->start_thread(sensor, &sensor->ir.image);
    //rad_cloud_detection->start_thread(sensor, &sensor->ir.image);
  }

  //---------------------------
}

//Subfunction
void Manager::next_step(dat::base::Sensor* sensor){
  //---------------------------

  switch(step){
    case rad::detection::cloud::WAIT_VALIDATION:{
      rad_cloud_detection->validate_bbox(sensor);
      break;
    }
    case rad::detection::cloud::PROCESSING:{
      this->step = rad::detection::cloud::WAIT_VALIDATION;
      break;
    }
  }

  //---------------------------
}

}
