#include "Wheel.h"

#include <Engine/Namespace.h>
#include <Camera/Namespace.h>
#include <Data/Namespace.h>
#include <Operation/Namespace.h>
#include <Render/Namespace.h>


namespace dat::gui{

//Constructor / Destructor
Wheel::Wheel(dat::Node* node_data){
  //---------------------------

  eng::Node* node_engine = node_data->get_node_engine();
  cam::Node* node_camera = node_data->get_node_camera();

  this->cam_control = node_camera->get_control();
  this->dat_graph = node_data->get_data_graph();
  this->ope_operation = new ope::Operation();

  this->mode = WHEEL_CAM_Z;

  //---------------------------
}
Wheel::~Wheel(){}

//Main function
void Wheel::change_mode(){
  //---------------------------

  this->mode--;
  if(mode == -1) mode = sizeof(Wheel_mode) - 1;

  //---------------------------
}
void Wheel::make_action(float direction){
  utl::type::Element* element = dat_graph->get_selected_element();
  //---------------------------

  //Rotation quantity
  float radian = 5 * M_PI/180 * 50;
  glm::vec3 R;

  switch (mode) {
    case WHEEL_R_Z:{
      R = glm::vec3(0, 0, direction * radian);
      ope_operation->make_rotation(element, R);
      break;
    }
    case WHEEL_R_Y:{
      R = glm::vec3(0, direction * radian, 0);
      ope_operation->make_rotation(element, R);
      break;
    }
    case WHEEL_R_X:{
      R = glm::vec3(direction * radian, 0, 0);
      ope_operation->make_rotation(element, R);
      break;
    }
    case WHEEL_CAM_Z:{
      cam_control->control_wheel(direction * radian);
      break;
    }
    default:
      break;
  }

  //---------------------------
}

//Subfunction
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
