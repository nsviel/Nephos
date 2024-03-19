#include "Sphere.h"

#include <Scene/Namespace.h>
#include <Engine/Namespace.h>
#include <Operation/Namespace.h>


namespace glyph::scene{

//Constructor / destructor
Sphere::Sphere(eng::Node* node_engine) : Glyph(node_engine){
  //---------------------------

  eng::scene::Node* node_scene = node_engine->get_node_scene();
  this->sce_loader = node_scene->get_scene_loader();
  this->ope_transform = new ope::Transformation();

  this->name = "world::sphere";
  this->is_visible = true;
  this->is_suppressible = false;
  this->is_movable = false;
  this->is_permanent = true;
  this->color = vec4(1, 0, 0, 0.5);
  this->path = "../media/glyph/sphere.obj";

  //---------------------------
}
Sphere::~Sphere(){}

//Main function
void Sphere::create(){
  //---------------------------

  data = *sce_loader->load_data(path);
  data.name = "world::sphere::data";
  data.is_visible = true;
  data.topology.type = utl::topology::TRIANGLE;

  vector<vec4>& rgb = data.rgb;
  for(int j=0; j<data.xyz.size(); j++){
    rgb[j] = color;
  }

  this->init();

  //---------------------------
}
void Sphere::update_glyph(){
  //---------------------------



  //---------------------------
}
void Sphere::reset_glyph(){
  //---------------------------

  data.is_visible = false;
  pose.model = mat4(1.0f);

  //---------------------------
}

//Subfunction
void Sphere::move_sphere(vec3 coordinate){
  //---------------------------

  data.is_visible = true;

  mat4 truc = glm::mat4(1.0f);
  float scaleFactor = 0.1f;
  truc = glm::scale(truc, glm::vec3(scaleFactor));

  truc[0][3] = coordinate.x;
  truc[1][3] = coordinate.y;
  truc[2][3] = coordinate.z;
  pose.model = truc;

  this->update_data();
  this->update_pose();

  //---------------------------
}

}
