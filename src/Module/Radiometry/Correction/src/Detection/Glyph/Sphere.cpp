#include "Sphere.h"

#include <Engine/Namespace.h>
#include <Camera/Namespace.h>
#include <IO/Namespace.h>
#include <glm/gtc/matrix_transform.hpp>


namespace rad::cor::glyph{

//Constructor / destructor
Sphere::Sphere(core::Node* node_core){
  //---------------------------
/*
  io::Node* node_io = node_core->get_node_io();
  cam::Node* node_camera = node_core->get_node_camera();
  io::imp::Node* node_importer = node_io->get_node_importer();

  this->io_importer = node_importer->get_io_importer();
  this->cam_control = node_camera->get_cam_control();

  this->name = "object::sphere";
  this->is_suppressible = false;
  this->pose->is_movable = false;
  this->is_permanent = true;
  this->color = glm::vec4(1, 0, 0, 0.5);
  this->path = "../media/glyph/sphere.obj";
*/
  //---------------------------
}
Sphere::~Sphere(){}

//Main function
void Sphere::create(){
  //---------------------------
/*
  //Retrieve data from file
  data = *io_importer->load_data(path);
  data->name = "object::sphere::data";
  data->is_visible = false;
  data->topology.type = utl::topology::TRIANGLE;

  this->construct(color);
*/
  //---------------------------
}
void Sphere::update_pose(dat::base::Entity& entity){
  //---------------------------

  if(mat_model != glm::mat4(1.0f)){
    utl::base::Pose& entity_pose = *entity.pose;
    pose->model = mat_model * entity_pose.model;

    cam_control->compute_camera_mvp(*pose);
  }

  //---------------------------
}
void Sphere::reset_glyph(){
  //---------------------------

  data->is_visible = false;

  //---------------------------
}

//Subfunction
void Sphere::construct(glm::vec4 color){
  //---------------------------

  data->rgba = std::vector<glm::vec4>(data->xyz.size(), glm::vec4(0, 0, 0, 0));
  for(int j=0; j<data->xyz.size(); j++){
    data->rgba[j] = color;
  }

  //---------------------------
}
void Sphere::move_sphere(glm::vec3 coordinate, float diameter){
  //---------------------------

  //Set visibility
  data->is_visible = true;

  //Set scale (raw sphere is 2m diameter)
  static float diameter_old = 0;
  if(diameter != diameter_old){
    float sphere_diameter = 2;
    mat_model = glm::mat4(1.0f);
    mat_model = glm::scale(mat_model, glm::vec3(diameter / sphere_diameter));
  }

  //Set detected sphere coordinate
  mat_model[0][3] = coordinate.x;
  mat_model[1][3] = coordinate.y;
  mat_model[2][3] = coordinate.z;

  //---------------------------
}

}
