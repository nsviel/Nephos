#include "Axis.h"


namespace glyph::grid{

//Constructor / destructor
Axis::Axis(eng::Node* node_engine) : Glyph(node_engine){
  //---------------------------

  this->name = "grid::axis";
  this->is_permanent = true;
  this->color = vec4(0.4f, 0.4f, 0.4f, 1.0f);

  //---------------------------
}
Axis::~Axis(){}

void Axis::create(){
  //---------------------------

  data.name = "grid::axis::data";
  data.width = 2;
  data.is_visible = true;
  data.topology.type = utl::topology::LINE;
  data.unicolor = color;

  //---------------------------
}

//Subfunction
void Axis::construct(int nb_cell){
  vector<vec3>& XYZ = data.xyz;
  vector<vec4>& RGB = data.rgb;
  float z = -0.001;
  //---------------------------

  //Parameters
  XYZ.clear();
  RGB.clear();

  //X axis
  vec4 rgb_x = vec4(0.4f, 0.3f, 0.3f, 1.0f);
  XYZ.push_back(vec3(-nb_cell, 0, z));
  XYZ.push_back(vec3(nb_cell, 0, z));
  RGB.push_back(rgb_x);
  RGB.push_back(rgb_x);

  //Y axis
  vec4 rgb_y = vec4(0.3f, 0.4f, 0.3f, 1.0f);
  XYZ.push_back(vec3(0, -nb_cell, z));
  XYZ.push_back(vec3(0, nb_cell, z));
  RGB.push_back(rgb_y);
  RGB.push_back(rgb_y);

  //---------------------------
}

}
