#include "Process.h"

#include <Utility/Namespace.h>
#include <Radiometry/Namespace.h>
#include <Dynamic/Namespace.h>
#include <Data/Namespace.h>


namespace rad::correction{

//Constructor / Destructor
Process::Process(rad::correction::Node* node_correction){
  //---------------------------

  rad::Node* node_radio = node_correction->get_node_radio();
  dat::Node* node_data = node_radio->get_node_data();

  this->rad_struct = node_correction->get_rad_struct();
  this->rad_glyph = new rad::correction::Glyph(node_correction);
  this->rad_image_detection = new rad::correction::image::Detection(node_correction);
  this->rad_cloud_detection = new rad::correction::cloud::Detection(node_correction);
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
  //---------------------------

  //Verify that we have a sensor type
  dat::base::Entity* entity = dat_selection->get_selected_entity();
  dyn::base::Sensor* sensor = dynamic_cast<dyn::base::Sensor*>(entity);
  if(sensor == nullptr) return;

  //Update glyph pose
  rad_glyph->update_sphere_glyph();

  //Cloud and image detection stuff
  rad_image_detection->start_thread(sensor);
  rad_cloud_detection->start_thread(sensor);

  //---------------------------
}

//Subfunction
void Process::step_detection(){
  //---------------------------

  //Verify that we have a sensor type
  dat::base::Entity* entity = dat_selection->get_selected_entity();
  dyn::base::Sensor* sensor = dynamic_cast<dyn::base::Sensor*>(entity);
  if(sensor == nullptr) return;

  //Detection step logic
  switch(rad_struct->state.detection){
    case rad::correction::detection::WAIT_VALIDATION:{
      rad_struct->state.detection = rad::correction::detection::PROCESSING;
      break;
    }
    case rad::correction::detection::PROCESSING:{
      rad_struct->state.detection = rad::correction::detection::WAIT_VALIDATION;
      rad_struct->state.measure = rad::correction::measure::WAIT_VALIDATION;
      break;
    }
  }

  //---------------------------
}
void Process::step_measure(){
  //---------------------------

  //Verify that we have a sensor type
  dat::base::Entity* entity = dat_selection->get_selected_entity();
  dyn::base::Sensor* sensor = dynamic_cast<dyn::base::Sensor*>(entity);
  if(sensor == nullptr) return;

  //Measurement step logic
  switch(rad_struct->state.measure){
    case rad::correction::measure::WAIT_VALIDATION:{
      if(rad_struct->state.detection == rad::correction::detection::PROCESSING){
        rad_cloud_detection->validate_bbox(sensor);
        rad_struct->state.measure = rad::correction::measure::PROCESSING;
      }
      break;
    }
    case rad::correction::measure::PROCESSING:{
      rad_struct->state.measure = rad::correction::measure::WAIT_VALIDATION;
      break;
    }
  }

  //---------------------------
}

}
