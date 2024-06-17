#include "Process.h"

#include <Utility/Namespace.h>
#include <Radiometry/Namespace.h>
#include <Dynamic/Namespace.h>
#include <Data/Namespace.h>


namespace rad::correction{

//Constructor / Destructor
Process::Process(rad::correction::Node* node_detection){
  //---------------------------

  rad::Node* node_radio = node_detection->get_node_radio();
  dat::Node* node_data = node_radio->get_node_data();

  this->rad_struct = node_detection->get_rad_struct();
  this->rad_glyph = new rad::correction::Glyph(node_detection);
  this->rad_image_detection = new rad::correction::image::Detection(node_detection);
  this->rad_cloud_detection = new rad::correction::cloud::Detection(node_detection);
  this->dat_selection = node_data->get_dat_selection();
  this->dat_image = node_data->get_dat_image();

  //---------------------------
}
Process::~Process(){}

//Main function
void Process::init(){
  //---------------------------

  rad_glyph->create_sphere_glyph();

  //---------------------------
}
void Process::loop(){
  dat::base::Entity* entity = dat_selection->get_selected_entity();
  dyn::base::Sensor* sensor = dynamic_cast<dyn::base::Sensor*>(entity);
  //---------------------------

  rad_glyph->update_sphere_glyph();

  //Working image


  //Cloud and image detection stuff
  rad_image_detection->start_thread(sensor);
  rad_cloud_detection->start_thread(sensor);

  //---------------------------
}

//Subfunction
void Process::step_detection(){
  dat::base::Entity* entity = dat_selection->get_selected_entity();
  //---------------------------

  //Verify that we have a sensor type
  dyn::base::Sensor* sensor = dynamic_cast<dyn::base::Sensor*>(entity);
  if(sensor == nullptr) return;

  //Measurement step logic
  int& step = rad_struct->sphere.state_step;
  switch(step){
    case rad::correction::VALIDATION:{
      rad_cloud_detection->validate_bbox(sensor);
      break;
    }
    case rad::correction::PROCESSING:{
      step = rad::correction::VALIDATION;
      break;
    }
  }

  //---------------------------
}

}
