#include "Plane.h"

#include <Element/Namespace.h>


namespace dat::glyph::grid{

//Constructor / destructor
Plane::Plane(){
  //---------------------------

  this->name = "grid::plane";
  this->is_permanent = true;
  this->color = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);

  //---------------------------
}
Plane::~Plane(){}

//Main function
void Plane::create(){
  //---------------------------

  data.name = "grid::plane::data";
  data.is_visible = true;
  data.topology.type = utl::topology::TRIANGLE;
  data.unicolor = color;

  //---------------------------
}

//Subfunction
void Plane::construct(int nb_cell){
  std::vector<glm::vec3>& xyz = data.xyz;
  std::vector<glm::vec4>& rgba = data.rgba;
  float z = -0.004;
  //---------------------------

  xyz.clear();
  rgba.clear();

  //Location
  xyz.push_back(glm::vec3(nb_cell, nb_cell, z));
  xyz.push_back(glm::vec3(-nb_cell, nb_cell, z));
  xyz.push_back(glm::vec3(-nb_cell, -nb_cell, z));

  xyz.push_back(glm::vec3(-nb_cell, -nb_cell, z));
  xyz.push_back(glm::vec3(nb_cell, -nb_cell, z));
  xyz.push_back(glm::vec3(nb_cell, nb_cell, z));

  //Color
  for(int j=0; j<xyz.size(); j++){
    rgba.push_back(glm::vec4(color.x, color.y, color.z, 1.0f));
  }

  //---------------------------
}

}
