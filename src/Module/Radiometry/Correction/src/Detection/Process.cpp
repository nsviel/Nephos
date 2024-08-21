#include "Process.h"

#include <Radiometry/Correction/Namespace.h>
#include <Data/Namespace.h>
#include <Utility/Namespace.h>


namespace rad::cor{

//Constructor / Destructor
Process::Process(rad::cor::Node* node_correction){
  //---------------------------

  dat::Node* node_data = node_correction->get_node_data();
  dat::gph::Node* node_graph = node_data->get_node_graph();
  dat::elm::Node* node_element = node_data->get_node_element();

  this->rad_struct = node_correction->get_rad_struct();
  this->rad_glyph = new rad::cor::Glyph(node_correction);
  this->rad_image_detection = new rad::cor::image::Detection(node_correction);
  this->rad_cloud_detection = new rad::cor::cloud::Detection(node_correction);
  this->gph_selection = node_graph->get_gph_selection();
  this->dat_image = node_element->get_dat_image();

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
  dat::base::Entity* entity = gph_selection->get_selected_entity();
  dat::base::Sensor* sensor = dynamic_cast<dat::base::Sensor*>(entity);
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
  dat::base::Entity* entity = gph_selection->get_selected_entity();
  dat::base::Sensor* sensor = dynamic_cast<dat::base::Sensor*>(entity);
  if(sensor == nullptr) return;

  //Detection step logic
  switch(rad_struct->state.detection){
    case rad::cor::detection::WAIT_VALIDATION:{
      rad_struct->state.detection = rad::cor::detection::PROCESSING;
      break;
    }
    case rad::cor::detection::PROCESSING:{
      rad_struct->state.detection = rad::cor::detection::WAIT_VALIDATION;
      rad_struct->state.measure = rad::cor::measure::WAIT_VALIDATION;
      break;
    }
  }

  //---------------------------
}
void Process::step_measure(){
  //---------------------------

  //Verify that we have a sensor type
  dat::base::Entity* entity = gph_selection->get_selected_entity();
  dat::base::Sensor* sensor = dynamic_cast<dat::base::Sensor*>(entity);
  if(sensor == nullptr) return;

  //Measurement step logic
  switch(rad_struct->state.measure){
    case rad::cor::measure::WAIT_VALIDATION:{
      if(rad_struct->state.detection == rad::cor::detection::PROCESSING){
        rad_cloud_detection->validate_bbox(sensor);
        rad_struct->state.measure = rad::cor::measure::PROCESSING;
      }
      break;
    }
    case rad::cor::measure::PROCESSING:{
      rad_struct->state.measure = rad::cor::measure::WAIT_VALIDATION;
      break;
    }
  }

  //---------------------------
}

}
