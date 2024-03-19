#include "Axis.h"

#include <Engine/Camera/Namespace.h>


namespace glyph::object{

//Constructor / destructor
Axis::Axis(eng::Node* node_engine) : Glyph(node_engine){
  //---------------------------

  this->name = "object::axis";
  this->is_permanent = true;
  this->is_visible = true;
  this->ope_transform = new ope::Transformation();
  this->type = utl::entity::object::AXIS;

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
void Axis::update_pose(utl::type::Entity* entity){
  //---------------------------

  utl::type::Pose* entity_pose = entity->get_pose();
  pose.model = entity_pose->model;

  eng::cam::Control* cam_control = node_camera->get_camera_control();
  cam_control->compute_camera_mvp(&pose);

  //---------------------------
}

//Subfunction
void Axis::construct(){
  vector<vec4>& rgb = data.rgb;
  vector<vec3>& xyz = data.xyz;
  //---------------------------

  //Location
  vec3 root = vec3(0, 0, 0);
  vec3 x = vec3(0.1,0,0);
  vec3 y = vec3(0,0.1,0);
  vec3 z = vec3(0,0,0.1);
  xyz.push_back(root);
  xyz.push_back(x);
  xyz.push_back(root);
  xyz.push_back(y);
  xyz.push_back(root);
  xyz.push_back(z);

  //Color
  rgb.push_back(vec4(0.9f, 0.2f, 0.2f, 1.0f));
  rgb.push_back(vec4(0.9f, 0.2f, 0.2f, 1.0f));
  rgb.push_back(vec4(0.2f, 0.9f, 0.2f, 1.0f));
  rgb.push_back(vec4(0.2f, 0.9f, 0.2f, 1.0f));
  rgb.push_back(vec4(0.2f, 0.2f, 0.9f, 1.0f));
  rgb.push_back(vec4(0.2f, 0.2f, 0.9f, 1.0f));

  //---------------------------
}

}
