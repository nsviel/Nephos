#include "Axis.h"


namespace glyph::grid{

//Constructor / destructor
Axis::Axis(Engine* engine) : Glyph(engine){
  //---------------------------

  this->is_permanent = true;
  this->color = vec4(0.4f, 0.4f, 0.4f, 1.0f);

  //---------------------------
}
Axis::~Axis(){}

void Axis::create(){
  if(vec_data.size() != 0) return;
  //---------------------------

  utl::base::Data* data = new utl::base::Data();
  data->draw_line_width = 2;
  data->is_visible = true;
  data->draw_type_name = "line";
  data->unicolor = color;
  this->vec_data.push_back(data);

  //---------------------------
}
void Axis::update_glyph(int nb_cell){
  vector<vec3>& XYZ = vec_data[0]->xyz;
  vector<vec4>& RGB = vec_data[0]->rgb;
  float z = -0.001;
  //---------------------------

  //Parameters
  XYZ.clear();
  RGB.clear();

  //X axis
  XYZ.push_back(vec3(-nb_cell, 0, z));
  XYZ.push_back(vec3(nb_cell, 0, z));
  RGB.push_back(color);
  RGB.push_back(color);

  //Y axis
  XYZ.push_back(vec3(0, -nb_cell, z));
  XYZ.push_back(vec3(0, nb_cell, z));
  RGB.push_back(color);
  RGB.push_back(color);

  //---------------------------
}

}
