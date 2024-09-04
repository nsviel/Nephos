#include "Axis.h"

#include <Data/Element/Namespace.h>


namespace dat::glyph::world{

//Constructor / destructor
Axis::Axis(){
  //---------------------------

  this->name = "world::axis";
  this->is_suppressible = false;
  this->is_permanent = true;
  this->pose->is_movable = false;

  //---------------------------
}
Axis::~Axis(){}

//Main function
void Axis::create(){
  //---------------------------

  data->name = "world::axis::data";
  data->width = 4;
  data->is_visible = true;
  data->topology.type = utl::topology::LINE;

  this->construct();

  //---------------------------
}

//Subfunction
void Axis::construct(){
  std::vector<glm::vec3>& xyz = data->xyz;
  std::vector<glm::vec4>& rgba = data->rgba;
  float z = 0;
  //---------------------------

  xyz.clear();
  rgba.clear();

  //X axis
  xyz.push_back(glm::vec3(0, 0, z));
  xyz.push_back(glm::vec3(1, 0, z));
  rgba.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
  rgba.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

  //Y axis
  xyz.push_back(glm::vec3(0, 0, z));
  xyz.push_back(glm::vec3(0, 1, z));
  rgba.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
  rgba.push_back(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));

  //Z axis
  xyz.push_back(glm::vec3(0, 0, z));
  xyz.push_back(glm::vec3(0, 0, 1));
  rgba.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
  rgba.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));

  //---------------------------
}

}
