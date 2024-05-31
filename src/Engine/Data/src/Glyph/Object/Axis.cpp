#include "Axis.h"

#include <Data/Namespace.h>
#include <Camera/Namespace.h>


namespace dat::glyph::object{

//Constructor / destructor
Axis::Axis(){
  //---------------------------

  this->name = "object::axis";
  this->is_permanent = false;
  this->type = dat::base::object::AXIS;

  //---------------------------
}
Axis::~Axis(){}

//Main function
void Axis::create(){
  //---------------------------
sayHello();
  //Create glyph
  data.name = "object::axis::data";
  data.width = 3;
  data.is_visible = true;
  data.topology.type = utl::topology::LINE;

  this->construct();

  //---------------------------
}
void Axis::update_pose(dat::base::Entity* entity){
  //---------------------------

  utl::base::Pose* entity_pose = &entity->pose;;
  pose.model = entity_pose->model;

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
