#include "Wheel.h"

#include <Core/Namespace.h>
#include <Engine/Namespace.h>
#include <Operation/Namespace.h>
#include <Utility/Namespace.h>
#include <Data/Namespace.h>
#include <Control/Namespace.h>


namespace ctr{

//Constructor / Destructor
Wheel::Wheel(ctr::Node* node_control){
  //---------------------------

  eng::Node* node_engine = node_control->get_node_engine();
  cam::Node* node_camera = node_engine->get_node_camera();
  dat::Node* node_data = node_control->get_node_data();
  dat::gph::Node* node_graph = node_data->get_node_graph();

  this->ctr_struct = node_control->get_ctr_struct();
  this->dat_selection = node_graph->get_dat_selection();
  this->trf_operation = new eng::trf::Operation();
  this->ope_location = new dat::atr::Location();
  this->cam_control = node_camera->get_cam_control();

  //---------------------------
}
Wheel::~Wheel(){}

//Main function
void Wheel::make_action(float value){
  utl::base::Element* element = dat_selection->get_selected_element();
  if(element == nullptr) return;
  //---------------------------

  //Rotation quantity
  float direction = math::sign(value);
  float radian = 5 * M_PI/180 * 50;
  glm::vec3 R;

  switch(ctr_struct->wheel_mode){
    case ctr::wheel::R_Z:{
      R = glm::vec3(0, 0, direction * radian);
      ope_location->compute_COM(element);
      trf_operation->make_rotation(element, element->pose.COM, R);
      break;
    }
    case ctr::wheel::R_Y:{
      R = glm::vec3(0, direction * radian, 0);
      ope_location->compute_COM(element);
      trf_operation->make_rotation(element, element->pose.COM, R);
      break;
    }
    case ctr::wheel::R_X:{
      R = glm::vec3(direction * radian, 0, 0);
      ope_location->compute_COM(element);
      trf_operation->make_rotation(element, element->pose.COM, R);
      break;
    }
    case ctr::wheel::CAM_Z:{
      cam_control->control_wheel(direction * radian);
      break;
    }
    default:{
      break;
    }
  }

  //---------------------------
}

//Subfunction
void Wheel::change_mode(){
  int& mode = ctr_struct->wheel_mode;
  //---------------------------

  mode--;
  if(mode == -1) mode = sizeof(ctr::wheel::Mode) - 1;

  //---------------------------
}
std::vector<const char*> Wheel::get_vec_mode(){
  std::vector<const char*> vec_mode;
  //---------------------------

  vec_mode.push_back("R_X");
  vec_mode.push_back("R_Y");
  vec_mode.push_back("R_Z");
  vec_mode.push_back("CAM_Z");

  //---------------------------
  return vec_mode;
}

}
