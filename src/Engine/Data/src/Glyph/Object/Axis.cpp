#include "Axis.h"

#include <Data/Namespace.h>
#include <Camera/Namespace.h>


namespace dat::glyph::object{

//Constructor / destructor
Axis::Axis(eng::Node* node_engine) : Glyph(node_engine){
  //---------------------------

  this->name = "object::axis";
  this->is_permanent = true;
  this->is_visible = true;
  this->type = dat::object::glyph::AXIS;

  //---------------------------
}
Axis::~Axis(){}

//Main function
void Axis::create(){
  //---------------------------

  //Create glyph
  data.name = "object::axis::data";
  data.width = 3;
  data.is_visible = is_visible;
  data.topology.type = utl::topology::LINE;

  this->construct();

  //---------------------------
}
void Axis::update_pose(dat::base::Entity* entity){
  //---------------------------
sayHello();
  utl::base::Pose* entity_pose = entity->get_pose();
  pose.model = entity_pose->model;

  cam::Control* cam_control = node_camera->get_cam_control();
  cam_control->compute_camera_mvp(&pose);

  //---------------------------
}

//Subfunction
void Axis::construct(){
  std::vector<glm::vec4>& rgba = data.rgba;
  std::vector<glm::vec3>& xyz = data.xyz;
  //---------------------------

  //Location
  glm::vec3 root = vec3(0, 0, 0);
  glm::vec3 x = vec3(0.1,0,0);
  glm::vec3 y = vec3(0,0.1,0);
  glm::vec3 z = vec3(0,0,0.1);
  xyz.push_back(root);
  xyz.push_back(x);
  xyz.push_back(root);
  xyz.push_back(y);
  xyz.push_back(root);
  xyz.push_back(z);

  //Color
  rgba.push_back(glm::vec4(0.9f, 0.2f, 0.2f, 1.0f));
  rgba.push_back(glm::vec4(0.9f, 0.2f, 0.2f, 1.0f));
  rgba.push_back(glm::vec4(0.2f, 0.9f, 0.2f, 1.0f));
  rgba.push_back(glm::vec4(0.2f, 0.9f, 0.2f, 1.0f));
  rgba.push_back(glm::vec4(0.2f, 0.2f, 0.9f, 1.0f));
  rgba.push_back(glm::vec4(0.2f, 0.2f, 0.9f, 1.0f));

  //---------------------------
}

}
