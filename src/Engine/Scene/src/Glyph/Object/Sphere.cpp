#include "Sphere.h"

#include <Scene/Namespace.h>
#include <Engine/Namespace.h>


namespace glyph::scene{

//Constructor / destructor
Sphere::Sphere(eng::Node* node_engine) : Glyph(node_engine){
  //---------------------------

  eng::scene::Node* node_scene = node_engine->get_node_scene();

  this->name = "world::sphere";
  this->is_visible = true;
  this->is_suppressible = false;
  this->is_movable = false;
  this->is_permanent = true;
  this->path = "../media/glyph/sphere.obj";

  //---------------------------
}
Sphere::~Sphere(){}

//Main function
void Sphere::create(){
  if(vec_data.size() != 0) return;
  //---------------------------

  utl::type::Data* data = new utl::type::Data();
  data->name = "world::sphere::data";
  data->is_visible = true;
  data->topology.type = utl::topology::TRIANGLE;
  this->vec_data.push_back(data);

  //---------------------------
  this->update_glyph();
}
void Sphere::update_glyph(){
  //---------------------------

  this->construct();

  //---------------------------
}

//Subfunction
void Sphere::construct(){
  vector<vec3>& XYZ = vec_data[0]->xyz;
  vector<vec4>& RGB = vec_data[0]->rgb;
  float z = 0;
  //---------------------------



  //---------------------------
}

}
