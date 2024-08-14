#include "Wheel.h"

#include <Engine/Namespace.h>
#include <Camera/Namespace.h>
#include <Data/Namespace.h>
#include <Operation/Namespace.h>
#include <Utility/Namespace.h>
#include <Interface/Namespace.h>


namespace itf::control{

//Constructor / Destructor
Wheel::Wheel(itf::Node* node_interface){
  //---------------------------

  dat::Node* node_data = node_interface->get_node_data();

  this->itf_struct = node_interface->get_itf_struct();
  this->node_engine = node_interface->get_node_engine();
  this->dat_selection = node_data->get_dat_selection();
  this->ope_operation = new ope::Operation();
  this->ope_location = new ope::attribut::Location();

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

  switch(itf_struct->control.wheel_mode){
    case WHEEL_R_Z:{
      R = glm::vec3(0, 0, direction * radian);
      ope_location->compute_COM(element);
      ope_operation->make_rotation(element, element->pose.COM, R);
      break;
    }
    case WHEEL_R_Y:{
      R = glm::vec3(0, direction * radian, 0);
      ope_location->compute_COM(element);
      ope_operation->make_rotation(element, element->pose.COM, R);
      break;
    }
    case WHEEL_R_X:{
      R = glm::vec3(direction * radian, 0, 0);
      ope_location->compute_COM(element);
      ope_operation->make_rotation(element, element->pose.COM, R);
      break;
    }
    case WHEEL_CAM_Z:{
      cam::Node* node_camera = node_engine->get_node_camera();
      cam::Control* cam_control = node_camera->get_cam_control();
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
  int& mode = itf_struct->control.wheel_mode;
  //---------------------------

  mode--;
  if(mode == -1) mode = sizeof(itf::control::Wheel_mode) - 1;

  //---------------------------
}
std::vector<const char*> Wheel::get_vec_mode(){
  std::vector<const char*> vec_mode;
  //---------------------------

  vec_mode.push_back("WHEEL_R_X");
  vec_mode.push_back("WHEEL_R_Y");
  vec_mode.push_back("WHEEL_R_Z");
  vec_mode.push_back("WHEEL_CAM_Z");

  //---------------------------
  return vec_mode;
}

}
