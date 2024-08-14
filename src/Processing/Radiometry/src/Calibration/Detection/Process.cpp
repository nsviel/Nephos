#include "Process.h"

#include <Utility/Namespace.h>
#include <Radiometry/Namespace.h>
#include <Dynamic/Namespace.h>
#include <Data/Namespace.h>


namespace rad::calibration{

//Constructor / Destructor
Process::Process(rad::calibration::Node* node_detection){
  //---------------------------

  rad::Node* node_radio = node_detection->get_node_radio();
  dat::Node* node_data = node_radio->get_node_data();

  this->rad_struct = node_detection->get_rad_struct();
  this->dat_selection = node_data->get_dat_selection();
  this->rad_detection = new rad::calibration::Detection(node_detection);

  //---------------------------
}
Process::~Process(){}

//Main function
void Process::init(){
  //---------------------------


  //---------------------------
}
void Process::loop(){
  //---------------------------

  dat::base::Entity* entity = dat_selection->get_selected_entity();
  dyn::base::Sensor* sensor = dynamic_cast<dyn::base::Sensor*>(entity);
  if(sensor == nullptr) return;

  rad_detection->start_thread(sensor);

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
  int& step = rad_struct->state.detection;
  switch(step){
    case rad::calibration::detection::WAIT_VALIDATION:{

      break;
    }
    case rad::calibration::detection::PROCESSING:{
      step = rad::calibration::detection::WAIT_VALIDATION;
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
    case rad::calibration::measure::WAIT_VALIDATION:{
      if(rad_struct->state.detection == rad::calibration::detection::PROCESSING){
        //rad_cloud_detection->validate_bbox(sensor);
        rad_struct->state.measure = rad::calibration::measure::PROCESSING;
      }
      break;
    }
    case rad::calibration::measure::PROCESSING:{
      rad_struct->state.measure = rad::calibration::measure::WAIT_VALIDATION;
      break;
    }
  }

  //---------------------------
}

}
