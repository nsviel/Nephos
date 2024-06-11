#include "Process.h"

#include <Utility/Namespace.h>
#include <Radiometry/Namespace.h>
#include <Data/Namespace.h>


namespace rad::detection::chart{

//Constructor / Destructor
Process::Process(rad::detection::Node* node_detection){
  //---------------------------

  this->rad_struct = node_detection->get_rad_struct();

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
  int& step = rad_struct->chart.state_step;
  switch(step){
    case rad::detection::VALIDATION:{

      break;
    }
    case rad::detection::PROCESSING:{
      step = rad::detection::VALIDATION;
      break;
    }
  }

  //---------------------------
}

}
