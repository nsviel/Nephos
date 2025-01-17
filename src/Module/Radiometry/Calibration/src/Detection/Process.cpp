#include "Process.h"

#include <Radiometry/Calibration/Namespace.h>
#include <Data/Namespace.h>
#include <Utility/Namespace.h>


namespace rad::cal{

//Constructor / Destructor
Process::Process(rad::cal::Node* node_detection){
  //---------------------------

  dat::Node* node_data = node_detection->get_node_data();
  dat::gph::Node* node_graph = node_data->get_node_graph();

  this->rad_struct = node_detection->get_rad_struct();
  this->gph_selection = node_graph->get_gph_selection();
  this->rad_detection = new rad::cal::Detection(node_detection);

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

  std::shared_ptr<dat::base::Entity> entity = gph_selection->get_selected_entity();
  auto sensor = std::dynamic_pointer_cast<dat::base::Sensor>(entity);
  if(!sensor) return;

  rad_detection->start_thread(sensor);

  //---------------------------
}

//Subfunction
void Process::step_detection(){
  std::shared_ptr<dat::base::Entity> entity = gph_selection->get_selected_entity();
  //---------------------------

  //Verify that we have a sensor type
  auto sensor = std::dynamic_pointer_cast<dat::base::Sensor>(entity);
  if(!sensor) return;

  //Measurement step logic
  int& step = rad_struct->state.detection;
  switch(step){
    case rad::cal::detection::WAIT_VALIDATION:{

      break;
    }
    case rad::cal::detection::PROCESSING:{
      step = rad::cal::detection::WAIT_VALIDATION;
      break;
    }
  }

  //---------------------------
}
void Process::step_measure(){
  //---------------------------

  //Verify that we have a sensor type
  std::shared_ptr<dat::base::Entity> entity = gph_selection->get_selected_entity();
  auto sensor = std::dynamic_pointer_cast<dat::base::Sensor>(entity);
  if(!sensor) return;

  //Measurement step logic
  switch(rad_struct->state.measure){
    case rad::cal::measure::WAIT_VALIDATION:{
      if(rad_struct->state.detection == rad::cal::detection::PROCESSING){
        //rad_cloud_detection->validate_bbox(sensor);
        rad_struct->state.measure = rad::cal::measure::PROCESSING;
      }
      break;
    }
    case rad::cal::measure::PROCESSING:{
      rad_struct->state.measure = rad::cal::measure::WAIT_VALIDATION;
      break;
    }
  }

  //---------------------------
}

}
