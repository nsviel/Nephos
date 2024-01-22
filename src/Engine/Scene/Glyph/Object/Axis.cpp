#include "Axis.h"


namespace glyph::object{

//Constructor / destructor
Axis::Axis(Engine* engine) : Glyph(engine){
  //---------------------------

  this->is_permanent = true;
  this->is_visible = true;
  this->ope_transform = new eng::ope::Transformation();

  //---------------------------
}
Axis::~Axis(){}

//Main function
void Axis::create(){
  if(vec_data.size() != 0) return;
  //---------------------------

  //Create glyph
  utl::type::Data* data = new utl::type::Data();
  data->draw_line_width = 3;
  data->is_visible = is_visible;
  data->draw_type_name = "line";
  this->vec_data.push_back(data);
  this->construct();

  //---------------------------
}
void Axis::update_glyph(utl::type::Data* entity){
  //---------------------------

  //ope_transform->make_transformation(vec_data[0], object->pose->COM, object->data->trans, object->data->rotat);

  //---------------------------
}

//Subfunction
void Axis::construct(){
  vector<vec4>& RGB = vec_data[0]->rgb;
  vector<vec3>& XYZ = vec_data[0]->xyz;
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
