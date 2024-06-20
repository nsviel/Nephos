#include "Process.h"

#include <Utility/Namespace.h>
#include <Radiometry/Namespace.h>
#include <Dynamic/Namespace.h>
#include <Data/Namespace.h>


namespace rad::calibration{

//Constructor / Destructor
Process::Process(rad::correction::Node* node_detection){
  //---------------------------

  rad::Node* node_radio = node_detection->get_node_radio();
  dat::Node* node_data = node_radio->get_node_data();

  this->rad_struct = node_detection->get_rad_struct();
  this->dat_selection = node_data->get_dat_selection();
  this->chart_detection = new rad::calibration::Detection(node_detection);

  //---------------------------
}
Process::~Process(){}

//Main function
void Process::init(){
  //---------------------------


  //---------------------------
}
void Process::loop(){
  dat::base::Entity* entity = dat_selection->get_selected_entity();
  dyn::base::Sensor* sensor = dynamic_cast<dyn::base::Sensor*>(entity);
  //---------------------------

  //chart_detection->start_thread(sensor);

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
  int& step = rad_struct->state_step;
  switch(step){
    case rad::correction::cloud::WAIT_VALIDATION:{

      break;
    }
    case rad::correction::cloud::PROCESSING:{
      step = rad::correction::cloud::WAIT_VALIDATION;
      break;
    }
  }

  //---------------------------
}

}
