#include "Wheel.h"

#include <Core/Namespace.h>
#include <Camera/Namespace.h>
#include <Data/Namespace.h>
#include <Operation/Namespace.h>
#include <Utility/Namespace.h>
#include <Graph/Namespace.h>
#include <Control/Namespace.h>


namespace ctl{

//Constructor / Destructor
Wheel::Wheel(ctl::Node* node_control){
  //---------------------------

  dat::Node* node_data = node_control->get_node_data();
  dat::graph::Node* node_graph = node_data->get_node_graph();

  this->ctl_struct = node_control->get_ctl_struct();
  this->node_engine = node_control->get_node_engine();
  this->dat_selection = node_graph->get_dat_selection();
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

  switch(ctl_struct->wheel_mode){
    case ctl::wheel::R_Z:{
      R = glm::vec3(0, 0, direction * radian);
      ope_location->compute_COM(element);
      ope_operation->make_rotation(element, element->pose.COM, R);
      break;
    }
    case ctl::wheel::R_Y:{
      R = glm::vec3(0, direction * radian, 0);
      ope_location->compute_COM(element);
      ope_operation->make_rotation(element, element->pose.COM, R);
      break;
    }
    case ctl::wheel::R_X:{
      R = glm::vec3(direction * radian, 0, 0);
      ope_location->compute_COM(element);
      ope_operation->make_rotation(element, element->pose.COM, R);
      break;
    }
    case ctl::wheel::CAM_Z:{
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
  int& mode = ctl_struct->wheel_mode;
  //---------------------------

  mode--;
  if(mode == -1) mode = sizeof(ctl::wheel::Mode) - 1;

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
