#include "Sphere.h"

#include <Data/Namespace.h>
#include <Engine/Namespace.h>
#include <Operation/Namespace.h>
#include <Camera/Namespace.h>
#include <Loader/Namespace.h>


namespace dat::glyph::object{

//Constructor / destructor
Sphere::Sphere(){
  //---------------------------

  //ldr::Node* node_loader = node_engine->get_node_loader();

  //this->ldr_loader = node_loader->get_ldr_importer();
  //this->ope_transform = new ope::Transformation();

  this->name = "object::sphere";
  this->is_suppressible = false;
  this->is_movable = false;
  this->is_permanent = true;
  this->color = glm::vec4(1, 0, 0, 0.5);
  this->path = "../media/glyph/sphere.obj";

  //---------------------------
}
Sphere::~Sphere(){}

//Main function
void Sphere::create(){
  //---------------------------

  //Retrieve data from file
  data = *ldr_loader->load_data(path);
  data.name = "object::sphere::data";
  data.is_visible = false;
  data.topology.type = utl::topology::TRIANGLE;

  this->construct(color);

  //---------------------------
}
void Sphere::update_pose(dat::base::Entity* entity){
  //---------------------------

  if(truc != glm::mat4(1.0f)){
    utl::base::Pose* entity_pose = entity->get_pose();
    pose.model = truc * entity_pose->model;

    //cam::Control* cam_control = node_camera->get_cam_control();
    //cam_control->compute_camera_mvp(&pose);
  }

  //---------------------------
}
void Sphere::reset_glyph(){
  //---------------------------

  data.is_visible = false;
  pose.model = glm::mat4(1.0f);

  //---------------------------
}

//Subfunction
void Sphere::construct(glm::vec4 color){
  //---------------------------

  std::vector<glm::vec4>& rgba = data.rgba;
  for(int j=0; j<data.xyz.size(); j++){
    rgba[j] = color;
  }

  //---------------------------
}
void Sphere::move_sphere(glm::vec3 coordinate, float diameter){
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
