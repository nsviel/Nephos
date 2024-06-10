#include "Manager.h"

#include <Utility/Namespace.h>
#include <Radiometry/Namespace.h>
#include <Operation/Namespace.h>
#include <Dynamic/Namespace.h>


namespace rad::detection{

//Constructor / Destructor
Manager::Manager(rad::Node* node_radio){
  //---------------------------

  dat::Node* node_data = node_radio->get_node_data();

  this->rad_struct = node_radio->get_rad_struct();
  this->rad_glyph = new rad::detection::glyph::Manager(node_radio);
  this->rad_image_detection = new rad::detection::image::Detection(node_radio);
  this->rad_cloud_detection = new rad::detection::cloud::Detection(node_radio);
  this->dat_selection = node_data->get_dat_selection();

  //---------------------------
}
Manager::~Manager(){}

//Main function
void Manager::init(){
  //---------------------------

  rad_glyph->create_sphere_glyph();

  //---------------------------
}
void Manager::loop(){
  dat::base::Entity* entity = dat_selection->get_selected_entity();
  dyn::base::Sensor* sensor = dynamic_cast<dyn::base::Sensor*>(entity);
  if(sensor == nullptr) return;
  //---------------------------

  //Cloud and image detection stuff
  rad_image_detection->start_thread(sensor);
  rad_cloud_detection->start_thread(sensor);

  //---------------------------
}

//Subfunction
void Manager::step_sphere_detection(){
  dat::base::Entity* entity = dat_selection->get_selected_entity();
  //---------------------------

  //Verify that we have a sensor type
  dyn::base::Sensor* sensor = dynamic_cast<dyn::base::Sensor*>(entity);
  if(sensor == nullptr) return;

  //Measurement step logic
  int& step = rad_struct->model.sphere.state_step;
  switch(step){
    case rad::detection::VALIDATION:{
      rad_cloud_detection->validate_bbox(sensor);
      step = rad::detection::PROCESSING;
      break;
    }
    case rad::detection::PROCESSING:{
      step = rad::detection::VALIDATION;
      break;
    }
  }

  //---------------------------
}
void Manager::step_chart_detection(){
  if(rad_struct->model.sphere.state_step == rad::detection::PROCESSING) return;
  //---------------------------

  rad_struct->model.chart.state_step = rad::detection::PROCESSING;
  //rad_cloud_detection->validate_bbox(sensor);

  //---------------------------
}

}
