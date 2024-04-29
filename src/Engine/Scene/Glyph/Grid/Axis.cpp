#include "Axis.h"

#include <Scene/Namespace.h>


namespace glyph::grid{

//Constructor / destructor
Axis::Axis(eng::Node* node_engine) : Glyph(node_engine){
  //---------------------------

  this->name = "grid::axis";
  this->is_permanent = true;
  this->color = vec4(0.4f, 0.4f, 0.4f, 1.0f);

  //---------------------------
}
Axis::~Axis(){}

void Axis::create(){
  //---------------------------

  data.name = "grid::axis::data";
  data.width = 2;
  data.is_visible = true;
  data.topology.type = utl::topology::LINE;
  data.unicolor = color;

  this->init();

  //---------------------------
}

//Subfunction
void Axis::construct(int nb_cell){
  vector<vec3>& xyz = data.xyz;
  vector<vec4>& rgb = data.rgb;
  float z = -0.001;
  //---------------------------

  //Parameters
  xyz.clear();
  rgb.clear();

  //X axis
  vec4 rgb_x = vec4(0.4f, 0.3f, 0.3f, 1.0f);
  xyz.push_back(vec3(-nb_cell, 0, z));
  xyz.push_back(vec3(nb_cell, 0, z));
  rgb.push_back(rgb_x);
  rgb.push_back(rgb_x);

  //Y axis
  vec4 rgb_y = vec4(0.3f, 0.4f, 0.3f, 1.0f);
  xyz.push_back(vec3(0, -nb_cell, z));
  xyz.push_back(vec3(0, nb_cell, z));
  rgb.push_back(rgb_y);
  rgb.push_back(rgb_y);

  //---------------------------
}

}
