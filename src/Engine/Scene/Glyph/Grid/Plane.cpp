#include "Plane.h"


namespace glyph::grid{

//Constructor / destructor
Plane::Plane(Engine* engine) : Glyph(engine){
  //---------------------------

  this->name = "grid_plane";
  this->color = vec4(0.2f, 0.2f, 0.2f, 1.0f);

  //---------------------------
}
Plane::~Plane(){}

void Plane::create(){
  if(vec_object.size() != 0) return;
  //---------------------------

  entity::Object* object = new entity::Object(engine);
  object->name = "grid_plane";
  object->is_visible = true;
  object->draw_type_name = "triangle";
  object->is_permanent = true;
  object->unicolor = color;
  this->vec_object.push_back(object);

  //---------------------------
}
void Plane::update_glyph(int nb_cell){
  vector<vec3>& XYZ = vec_object[0]->data->xyz;
  vector<vec4>& RGB = vec_object[0]->data->rgb;
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
