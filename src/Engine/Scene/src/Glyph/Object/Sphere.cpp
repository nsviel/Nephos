#include "Sphere.h"

#include <Scene/Namespace.h>
#include <Engine/Namespace.h>
#include <Operation/Namespace.h>
#include <Camera/Namespace.h>


namespace glyph::scene{

//Constructor / destructor
Sphere::Sphere(eng::Node* node_engine) : Glyph(node_engine){
  //---------------------------

  eng::scene::Node* node_scene = node_engine->get_node_scene();
  this->sce_loader = node_scene->get_scene_loader();
  this->ope_transform = new ope::Transformation();

  this->name = "world::sphere";
  this->is_visible = true;
  this->is_suppressible = false;
  this->is_movable = false;
  this->is_permanent = true;
  this->color = vec4(1, 0, 0, 0.5);
  this->path = "../media/glyph/sphere.obj";

  //---------------------------
}
Sphere::~Sphere(){}

//Main function
void Sphere::create(){
  //---------------------------

  data.name = "world::sphere::data";
  data.is_visible = true;
  data.topology.type = utl::topology::TRIANGLE;

  this->construct();
  this->init();

  //---------------------------
}
void Sphere::update_pose(utl::type::Entity* entity){
  //---------------------------

  utl::type::Pose* entity_pose = entity->get_pose();
  pose.model = truc * entity_pose->model;

  eng::cam::Control* cam_control = node_camera->get_camera_control();
  cam_control->compute_camera_mvp(&pose);

  //---------------------------
}
void Sphere::reset_glyph(){
  //---------------------------

  data.is_visible = false;
  pose.model = mat4(1.0f);

  //---------------------------
}

//Subfunction
void Sphere::construct(){
  //---------------------------

  //Retrieve data from file
  data = *sce_loader->load_data(path);

  //Assign color
  vector<vec4>& rgb = data.rgb;
  for(int j=0; j<data.xyz.size(); j++){
    rgb[j] = color;
  }

  //---------------------------
}
void Sphere::assign_color(vec4 color){
  //---------------------------

  vector<vec4>& rgb = data.rgb;
  for(int j=0; j<data.xyz.size(); j++){
    rgb[j] = color;
  }

  //---------------------------
}
void Sphere::move_sphere(vec3 coordinate){
  //---------------------------

  //Set visibility
  data.is_visible = true;

  //Set scale (original sphere is 1m diameter)
  truc = glm::mat4(1.0f);
  float scaleFactor = 0.1f;
  truc = glm::scale(truc, glm::vec3(scaleFactor));

  //Set detected sphere coordinate
  truc[0][3] = coordinate.x;
  truc[1][3] = coordinate.y;
  truc[2][3] = coordinate.z;

  //---------------------------
}

}
