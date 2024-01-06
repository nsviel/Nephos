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

void Axis::create(eng::data::Object* object){
  //---------------------------

  //Create glyph
  object->axis = new eng::data::Object();
  eng::data::Object* axis = object->axis;

  axis->name = "axis";
  axis->draw_line_width = 3;
  axis->is_visible = is_visible;
  axis->draw_type_name = "line";

  //Axis colors
  vector<vec4>& RGB = axis->rgb;
  RGB.push_back(vec4(0.9f, 0.2f, 0.2f, 1.0f));
  RGB.push_back(vec4(0.9f, 0.2f, 0.2f, 1.0f));
  RGB.push_back(vec4(0.2f, 0.9f, 0.2f, 1.0f));
  RGB.push_back(vec4(0.2f, 0.9f, 0.2f, 1.0f));
  RGB.push_back(vec4(0.2f, 0.2f, 0.9f, 1.0f));
  RGB.push_back(vec4(0.2f, 0.2f, 0.9f, 1.0f));

  vector<vec3>& XYZ = axis->xyz;
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
void Axis::update(eng::data::Object* object){
  //---------------------------

  ope_transform->make_transformation(object->axis, object->COM, object->trans, object->rotat);

  //---------------------------
}

}
