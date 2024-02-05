#include "Wheel.h"

#include <Engine/Namespace.h>


namespace eng::ope{

//Constructor / Destructor
Wheel::Wheel(eng::Node* engine){
  //---------------------------

  eng::scene::Node* node_scene = engine->get_node_scene();
  eng::cam::Node* node_camera = engine->get_node_camera();

  this->cam_control = node_camera->get_camera_control();
  this->sce_scene = node_scene->get_scene();
  this->ope_operation = new eng::ope::Operation();

  //---------------------------
}
Wheel::~Wheel(){}

//Main function


}
