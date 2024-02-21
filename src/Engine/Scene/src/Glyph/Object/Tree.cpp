#include "Tree.h"

#include <Utility/Function/Math/Math.h>


namespace glyph::object{

//Constructor / destructor
Tree::Tree(eng::Node* engine) : Glyph(engine){
  //---------------------------

  this->octreeManager = new ope::tree::Octree();

  this->name = "tree";
    this->is_permanent = true;
  this->is_visible = false;
  this->color = vec4(1, 1, 1, 0.7);
  this->level = 6;

  //---------------------------
}
Tree::~Tree(){}

//Main function
void Tree::create(){
  if(vec_data.size() != 0) return;
  //---------------------------

  //Create glyph
  utl::type::Data* data = new utl::type::Data();
  data->line.width = 2;
  data->is_visible = is_visible;
  data->draw_type = utl::topology::LINE;
  data->unicolor = color;
  this->vec_data.push_back(data);

  //---------------------------
}
void Tree::update_glyph(utl::type::Data* data){
  //---------------------------

  if(is_visible){
    //octreeManager->create_octree(cloud, level);
    vec_data[0]->point.xyz = data->point.xyz;
  }

  //---------------------------
}

}
