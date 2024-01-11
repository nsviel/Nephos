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
  if(vec_object.size() != 0) return;
  //---------------------------

  //Create glyph
  eng::data::Object* object = new eng::data::Object();
  object->name = "axis";
  object->draw_line_width = 3;
  object->is_visible = is_visible;
  object->draw_type_name = "line";
  this->vec_object.push_back(object);
  this->construct();

  //---------------------------
}
void Axis::update(eng::data::Entity* entity){
  //---------------------------

  if(eng::data::Object* object = dynamic_cast<eng::data::Object*>(entity)){
    ope_transform->make_transformation(vec_object[0], object->COM, object->trans, object->rotat);
  }

  //---------------------------
}

//Subfunction
void Axis::construct(){
  vector<vec4>& RGB = vec_object[0]->rgb;
  vector<vec3>& XYZ = vec_object[0]->xyz;
  //---------------------------

  //Location
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

  //Color
  RGB.push_back(vec4(0.9f, 0.2f, 0.2f, 1.0f));
  RGB.push_back(vec4(0.9f, 0.2f, 0.2f, 1.0f));
  RGB.push_back(vec4(0.2f, 0.9f, 0.2f, 1.0f));
  RGB.push_back(vec4(0.2f, 0.9f, 0.2f, 1.0f));
  RGB.push_back(vec4(0.2f, 0.2f, 0.9f, 1.0f));
  RGB.push_back(vec4(0.2f, 0.2f, 0.9f, 1.0f));

  //---------------------------
}

}
