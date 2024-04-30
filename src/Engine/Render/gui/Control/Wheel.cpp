#include "Wheel.h"

#include <Engine/Namespace.h>
#include <Camera/Namespace.h>
#include <Data/Namespace.h>
#include <Operation/Namespace.h>
#include <Render/Namespace.h>


namespace rnd::gui{

//Constructor / Destructor
Wheel::Wheel(rnd::Node* node_render){
  //---------------------------

  eng::Node* node_engine = node_render->get_node_engine();
  dat::Node* node_data = node_engine->get_node_data();
  cam::Node* node_camera = node_engine->get_node_camera();

  this->cam_control = node_camera->get_control();
  this->dat_database = node_data->get_database();
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
  //---------------------------

  //Rotation quantity
  float radian = 5 * M_PI/180 * 50;
  glm::vec3 R;

  switch (mode) {
    case WHEEL_R_Z:{
      dat::base::Set* set_scene = dat_database->get_set_graph();
      dat::base::Entity* entity = set_scene->selected_entity;
      R = glm::vec3(0, 0, direction * radian);
      ope_operation->make_rotation(entity->set_parent, R);
      break;
    }
    case WHEEL_R_Y:{
      dat::base::Set* set_scene = dat_database->get_set_graph();
      dat::base::Entity* entity = set_scene->selected_entity;
      R = glm::vec3(0, direction * radian, 0);
      ope_operation->make_rotation(entity->set_parent, R);
      break;
    }
    case WHEEL_R_X:{
      dat::base::Set* set_scene = dat_database->get_set_graph();
      dat::base::Entity* entity = set_scene->selected_entity;
      R = glm::vec3(direction * radian, 0, 0);
      ope_operation->make_rotation(entity->set_parent, R);
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
