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

  this->name = "object::sphere";
  this->is_visible = false;
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

  //Retrieve data from file
  data = *sce_loader->load_data(path);
  data.name = "object::sphere::data";
  data.is_visible = false;
  data.topology.type = utl::topology::TRIANGLE;

  this->construct(color);
  this->init();

  //---------------------------
}
void Sphere::update_pose(utl::type::Entity* entity){
  //---------------------------

  if(truc != mat4(1.0f)){
    utl::type::Pose* entity_pose = entity->get_pose();
    pose.model = truc * entity_pose->model;

    cam::Control* cam_control = node_camera->get_camera_control();
    cam_control->compute_camera_mvp(&pose);
  }

  //---------------------------
}
void Sphere::reset_glyph(){
  //---------------------------

  data.is_visible = false;
  pose.model = mat4(1.0f);

  //---------------------------
}

//Subfunction
void Sphere::construct(vec4 color){
  //---------------------------

  vector<vec4>& rgb = data.rgb;
  for(int j=0; j<data.xyz.size(); j++){
    rgb[j] = color;
  }

  //---------------------------
}
void Sphere::move_sphere(vec3 coordinate, float diameter){
  //---------------------------

  //Set scale (original sphere is 1m diameter)
  float sphere_diameter = 2;
  truc = glm::mat4(1.0f);
  truc = glm::scale(truc, glm::vec3(diameter / sphere_diameter));

  //Set detected sphere coordinate
  truc[0][3] = coordinate.x;
  truc[1][3] = coordinate.y;
  truc[2][3] = coordinate.z;

  //Set visibility
  data.is_visible = true;

  //---------------------------
}

}
