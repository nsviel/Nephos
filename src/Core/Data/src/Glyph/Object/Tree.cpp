#include "Tree.h"

#include <Data/Namespace.h>


namespace dat::glyph::object{

//Constructor / destructor
Tree::Tree(){
  //---------------------------

  this->octreeManager = new ope::tree::Octree();

  this->name = "tree";
  this->is_permanent = true;
  this->color = glm::vec4(1, 1, 1, 0.7);
  this->level = 6;
  this->type = dat::base::object::TREE;

  //---------------------------
}
Tree::~Tree(){}

//Main function
void Tree::create(){
  //---------------------------

  //Create glyph
  data.name = "tree::data";
  data.width = 2;
  data.is_visible = false;
  data.topology.type = utl::topology::LINE;
  data.unicolor = color;

  //---------------------------
}
void Tree::update_glyph(utl::base::Data* data){
  //---------------------------


  //---------------------------
}

}
