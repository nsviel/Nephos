#include "Plane.h"


namespace glyph::grid{

//Constructor / destructor
Plane::Plane(){
  //---------------------------

  this->name = "grid_plane";
  this->color = vec4(0.1f, 0.1f, 0.1f, 1.0f);
  this->nb_cell = 10;

  //---------------------------
}
Plane::~Plane(){
  //---------------------------

  delete data;

  //---------------------------
}

void Plane::create(){
  //---------------------------

  this->data = new eng::data::Object();
  data->is_visible = true;
  data->draw_type_name = "triangle";
  data->is_permanent = true;
  data->is_suppressible = false;
  data->unicolor = color;
  this->update();

  //---------------------------
}
void Plane::update(){
  vector<vec3>& XYZ = data->xyz;
  vector<vec4>& RGB = data->rgb;
  float z = -0.01;
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
