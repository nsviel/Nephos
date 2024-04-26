#include "Wheel.h"

#include <Engine/Namespace.h>
#include <Camera/Namespace.h>
#include <Scene/Namespace.h>
#include <Rendering/Namespace.h>


namespace rnd::gui{

//Constructor / Destructor
Wheel::Wheel(rnd::Node* node_rendering){
  //---------------------------

  eng::Node* node_engine = node_rendering->get_node_engine();
  eng::scene::Node* node_scene = node_engine->get_node_scene();
  eng::cam::Node* node_camera = node_engine->get_node_camera();

  this->cam_control = node_camera->get_camera_control();
  this->sce_database = node_scene->get_scene_database();
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
  vec3 R;

  switch (mode) {
    case WHEEL_R_Z:{
      utl::type::Set* set_scene = sce_database->get_set_scene();
      utl::type::Entity* entity = set_scene->selected_entity;
      R = vec3(0, 0, direction * radian);
      ope_operation->make_rotation(entity->set_parent, R);
      break;
    }
    case WHEEL_R_Y:{
      utl::type::Set* set_scene = sce_database->get_set_scene();
      utl::type::Entity* entity = set_scene->selected_entity;
      R = vec3(0, direction * radian, 0);
      ope_operation->make_rotation(entity->set_parent, R);
      break;
    }
    case WHEEL_R_X:{
      utl::type::Set* set_scene = sce_database->get_set_scene();
      utl::type::Entity* entity = set_scene->selected_entity;
      R = vec3(direction * radian, 0, 0);
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
vector<const char*> Wheel::get_vec_mode(){
  vector<const char*> vec_mode;
  //---------------------------

  vec_mode.push_back("WHEEL_R_X");
  vec_mode.push_back("WHEEL_R_Y");
  vec_mode.push_back("WHEEL_R_Z");
  vec_mode.push_back("WHEEL_CAM_Z");

  //---------------------------
  return vec_mode;
}

}
