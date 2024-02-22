#include "Axis.h"


namespace glyph::world{

//Constructor / destructor
Axis::Axis(eng::Node* engine) : Glyph(engine){
  //---------------------------

  this->name = "axis";
  this->is_visible = true;
  this->is_suppressible = false;
  this->is_movable = false;
  this->is_permanent = true;

  //---------------------------
}
Axis::~Axis(){}

//Main function
void Axis::create(){
  if(vec_data.size() != 0) return;
  //---------------------------

  utl::type::Data* data = new utl::type::Data();
  data->line.width = 4;
  data->is_visible = true;
  data->draw_type = utl::topology::LINE;
  this->vec_data.push_back(data);
  this->update_glyph();

  //---------------------------
}
void Axis::update_glyph(){
  //---------------------------

  this->construct();

  //---------------------------
}

//Subfunction
void Axis::construct(){
  vector<vec3>& XYZ = vec_data[0]->line.xyz;
  vector<vec4>& RGB = vec_data[0]->line.rgb;
  float z = 0;
  //---------------------------

  //X axis
  XYZ.push_back(vec3(0, 0, z));
  XYZ.push_back(vec3(1, 0, z));
  RGB.push_back(vec4(1.0f, 0.0f, 0.0f, 1.0f));
  RGB.push_back(vec4(1.0f, 0.0f, 0.0f, 1.0f));

  //Y axis
  XYZ.push_back(vec3(0, 0, z));
  XYZ.push_back(vec3(0, 1, z));
  RGB.push_back(vec4(0.0f, 1.0f, 0.0f, 1.0f));
  RGB.push_back(vec4(0.0f, 1.0f, 0.0f, 1.0f));

  //Z axis
  XYZ.push_back(vec3(0, 0, z));
  XYZ.push_back(vec3(0, 0, 1));
  RGB.push_back(vec4(0.0f, 0.0f, 1.0f, 1.0f));
  RGB.push_back(vec4(0.0f, 0.0f, 1.0f, 1.0f));

  //---------------------------
}

}
