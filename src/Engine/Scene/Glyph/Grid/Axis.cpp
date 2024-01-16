#include "Axis.h"


namespace glyph::grid{

//Constructor / destructor
Axis::Axis(Engine* engine) : Glyph(engine){
  //---------------------------

  this->color = vec4(0.4f, 0.4f, 0.4f, 1.0f);

  //---------------------------
}
Axis::~Axis(){}

void Axis::create(){
  if(vec_object.size() != 0) return;
  //---------------------------

  entity::Object* object = new entity::Object(engine);
  object->name = "grid_axis";
  object->data->draw_line_width = 2;
  object->is_visible = true;
  object->draw_type_name = "line";
  object->is_permanent = true;
  object->unicolor = color;
  this->vec_object.push_back(object);

  //---------------------------
}
void Axis::update_glyph(int nb_cell){
  vector<vec3>& XYZ = vec_object[0]->data->xyz;
  vector<vec4>& RGB = vec_object[0]->data->rgb;
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
