#include "Axis.h"

#include <Scene/Namespace.h>


namespace dat::glyph::world{

//Constructor / destructor
Axis::Axis(eng::Node* node_engine) : Glyph(node_engine){
  //---------------------------

  this->name = "world::axis";
  this->is_visible = true;
  this->is_suppressible = false;
  this->is_movable = false;
  this->is_permanent = true;

  //---------------------------
}
Axis::~Axis(){}

//Main function
void Axis::create(){
  //---------------------------

  data.name = "world::axis::data";
  data.width = 4;
  data.is_visible = true;
  data.topology.type = utl::topology::LINE;

  this->construct();
  this->init();

  //---------------------------
}

//Subfunction
void Axis::construct(){
  vector<vec3>& xyz = data.xyz;
  vector<vec4>& rgb = data.rgb;
  float z = 0;
  //---------------------------

  //X axis
  xyz.push_back(vec3(0, 0, z));
  xyz.push_back(vec3(1, 0, z));
  rgb.push_back(vec4(1.0f, 0.0f, 0.0f, 1.0f));
  rgb.push_back(vec4(1.0f, 0.0f, 0.0f, 1.0f));

  //Y axis
  xyz.push_back(vec3(0, 0, z));
  xyz.push_back(vec3(0, 1, z));
  rgb.push_back(vec4(0.0f, 1.0f, 0.0f, 1.0f));
  rgb.push_back(vec4(0.0f, 1.0f, 0.0f, 1.0f));

  //Z axis
  xyz.push_back(vec3(0, 0, z));
  xyz.push_back(vec3(0, 0, 1));
  rgb.push_back(vec4(0.0f, 0.0f, 1.0f, 1.0f));
  rgb.push_back(vec4(0.0f, 0.0f, 1.0f, 1.0f));

  //---------------------------
}

}
