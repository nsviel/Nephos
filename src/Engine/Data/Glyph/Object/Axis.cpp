#include "Axis.h"


namespace glyph::object{

//Constructor / destructor
Axis::Axis(){
  //---------------------------

  this->is_visible = true;
  this->ope_transform = new eng::ope::Transformation();

  //---------------------------
}
Axis::~Axis(){}

//Main function
void Axis::create(){
  //---------------------------

  //Create glyph
  data = new eng::data::Object();
  data->name = "axis";
  data->draw_line_width = 3;
  data->is_visible = is_visible;
  data->draw_type_name = "line";
  this->construct();

  //---------------------------
}
void Axis::update(eng::data::Object* object){
  //---------------------------

  ope_transform->make_transformation(data, object->COM, object->trans, object->rotat);

  //---------------------------
}

//Subfunction
void Axis::construct(){
  //---------------------------

  vector<vec4>& RGB = data->rgb;
  RGB.push_back(vec4(0.9f, 0.2f, 0.2f, 1.0f));
  RGB.push_back(vec4(0.9f, 0.2f, 0.2f, 1.0f));
  RGB.push_back(vec4(0.2f, 0.9f, 0.2f, 1.0f));
  RGB.push_back(vec4(0.2f, 0.9f, 0.2f, 1.0f));
  RGB.push_back(vec4(0.2f, 0.2f, 0.9f, 1.0f));
  RGB.push_back(vec4(0.2f, 0.2f, 0.9f, 1.0f));

  vector<vec3>& XYZ = data->xyz;
  vec3 root = vec3(0, 0, 0);
  vec3 x = vec3(0.1,0,0);
  vec3 y = vec3(0,0.1,0);
  vec3 z = vec3(0,0,0.1);
  XYZ.push_back(root);
  XYZ.push_back(x);
  XYZ.push_back(root);
  XYZ.push_back(y);
  XYZ.push_back(root);
  XYZ.push_back(z);

  //---------------------------
}

}
