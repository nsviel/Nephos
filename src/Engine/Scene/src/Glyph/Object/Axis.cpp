#include "Axis.h"

#include <Engine/Camera/Namespace.h>


namespace glyph::object{

//Constructor / destructor
Axis::Axis(eng::Node* engine) : Glyph(engine){
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
  if(vec_data.size() != 0) return;
  //---------------------------

  //Create glyph
  utl::type::Data* data = new utl::type::Data();
  data->name = "object::axis::data";
  data->width = 3;
  data->is_visible = is_visible;
  data->topology.type = utl::topology::LINE;
  this->vec_data.push_back(data);
  this->construct();

  //---------------------------
}
void Axis::update_pose(utl::type::Entity* entity){
  //---------------------------

  utl::type::Pose* entity_pose = entity->get_pose();
  pose->model = entity_pose->model;

  eng::cam::Control* cam_control = node_camera->get_camera_control();
  cam_control->compute_camera_mvp(pose);

  //---------------------------
}

//Subfunction
void Axis::construct(){
  vector<vec4>& RGB = vec_data[0]->rgb;
  vector<vec3>& XYZ = vec_data[0]->xyz;
  //---------------------------

  //Location
  vec3 root = vec3(0, 0, 0);
  vec3 x = vec3(0.1,0,0);
  vec3 y = vec3(0,0.1,0);
  vec3 z = vec3(0,0,0.1);
  XYZ.push_back(root);
  XYZ.push_back(x);
  XYZ.push_back(root);
  XYZ.push_back(y);
  XYZ.push_back(root);
  XYZ.push_back(z);

  //Color
  RGB.push_back(vec4(0.9f, 0.2f, 0.2f, 1.0f));
  RGB.push_back(vec4(0.9f, 0.2f, 0.2f, 1.0f));
  RGB.push_back(vec4(0.2f, 0.9f, 0.2f, 1.0f));
  RGB.push_back(vec4(0.2f, 0.9f, 0.2f, 1.0f));
  RGB.push_back(vec4(0.2f, 0.2f, 0.9f, 1.0f));
  RGB.push_back(vec4(0.2f, 0.2f, 0.9f, 1.0f));

  //---------------------------
}

}
