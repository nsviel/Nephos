#include "Plane.h"


namespace glyph::grid{

//Constructor / destructor
Plane::Plane(eng::Node* node_engine) : Glyph(node_engine){
  //---------------------------

  this->name = "grid::plane";
  this->is_permanent = true;
  this->color = vec4(0.2f, 0.2f, 0.2f, 1.0f);

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
  vector<vec3>& XYZ = data.xyz;
  vector<vec4>& RGB = data.rgb;
  float z = -0.004;
  //---------------------------

  XYZ.clear();
  RGB.clear();

  //Location
  XYZ.push_back(vec3(nb_cell, nb_cell, z));
  XYZ.push_back(vec3(-nb_cell, nb_cell, z));
  XYZ.push_back(vec3(-nb_cell, -nb_cell, z));

  XYZ.push_back(vec3(-nb_cell, -nb_cell, z));
  XYZ.push_back(vec3(nb_cell, -nb_cell, z));
  XYZ.push_back(vec3(nb_cell, nb_cell, z));

  //Color
  for(int j=0; j<XYZ.size(); j++){
    RGB.push_back(vec4(color.x, color.y, color.z, 1.0f));
  }

  //---------------------------
}

}
