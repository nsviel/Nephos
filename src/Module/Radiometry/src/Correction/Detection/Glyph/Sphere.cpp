#include "Sphere.h"

#include <Data/Namespace.h>
#include <Engine/Namespace.h>
#include <Operation/Namespace.h>
#include <Camera/Namespace.h>
#include <Loader/Namespace.h>


namespace rad::correction::glyph{

//Constructor / destructor
Sphere::Sphere(eng::Node* node_engine){
  //---------------------------

  ldr::Node* node_loader = node_engine->get_node_loader();
  cam::Node* node_camera = node_engine->get_node_camera();

  this->ldr_loader = node_loader->get_ldr_importer();
  this->cam_control = node_camera->get_cam_control();

  this->name = "object::sphere";
  this->is_suppressible = false;
  this->pose.movable = false;
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

  if(mat_model != glm::mat4(1.0f)){
    utl::base::Pose* entity_pose = &entity->pose;;
    pose.model = mat_model * entity_pose->model;

    cam_control->compute_camera_mvp(&pose);
  }

  //---------------------------
}
void Sphere::reset_glyph(){
  //---------------------------

  data.is_visible = false;

  //---------------------------
}

//Subfunction
void Sphere::construct(glm::vec4 color){
  //---------------------------

  data.rgba = std::vector<glm::vec4>(data.xyz.size(), vec4(0, 0, 0, 0));
  for(int j=0; j<data.xyz.size(); j++){
    data.rgba[j] = color;
  }

  //---------------------------
}
void Sphere::move_sphere(glm::vec3 coordinate, float diameter){
  //---------------------------

  //Set visibility
  data.is_visible = true;

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