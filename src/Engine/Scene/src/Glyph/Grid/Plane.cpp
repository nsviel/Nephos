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

void Plane::create(){
  if(vec_data.size() != 0) return;
  //---------------------------

  utl::type::Data* data = new utl::type::Data();
  data->name = "grid::plane::data";
  data->is_visible = true;
  data->topology.type = utl::topology::TRIANGLE;
  data->unicolor = color;
  this->vec_data.push_back(data);

  //---------------------------
}
void Plane::update_glyph(int nb_cell){
  vector<vec3>& XYZ = vec_data[0]->xyz;
  vector<vec4>& RGB = vec_data[0]->rgb;
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
