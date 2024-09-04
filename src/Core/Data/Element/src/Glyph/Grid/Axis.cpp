#include "Axis.h"

#include <Data/Element/Namespace.h>


namespace dat::glyph::grid{

//Constructor / destructor
Axis::Axis(){
  //---------------------------

  this->name = "grid::axis";
  this->is_permanent = true;
  this->color = glm::vec4(0.4f, 0.4f, 0.4f, 1.0f);

  //---------------------------
}
Axis::~Axis(){}

void Axis::create(){
  //---------------------------

  data->name = "grid::axis::data";
  data->width = 2;
  data->is_visible = true;
  data->topology.type = utl::topology::LINE;
  data->unicolor = color;

  //---------------------------
}

//Subfunction
void Axis::construct(int nb_cell){
  std::vector<glm::vec3>& xyz = data->xyz;
  std::vector<glm::vec4>& rgba = data->rgba;
  float z = -0.001;
  //---------------------------

  //Parameters
  xyz.clear();
  rgba.clear();

  //X axis
  glm::vec4 rgb_x = glm::vec4(0.4f, 0.3f, 0.3f, 1.0f);
  xyz.push_back(glm::vec3(-nb_cell, 0, z));
  xyz.push_back(glm::vec3(nb_cell, 0, z));
  rgba.push_back(rgb_x);
  rgba.push_back(rgb_x);

  //Y axis
  glm::vec4 rgb_y = glm::vec4(0.3f, 0.4f, 0.3f, 1.0f);
  xyz.push_back(glm::vec3(0, -nb_cell, z));
  xyz.push_back(glm::vec3(0, nb_cell, z));
  rgba.push_back(rgb_y);
  rgba.push_back(rgb_y);

  //---------------------------
}

}
