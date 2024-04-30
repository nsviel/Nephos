#include "Tree.h"

#include <Scene/Namespace.h>
#include <Data/Namespace.h>


namespace dat::glyph::object{

//Constructor / destructor
Tree::Tree(eng::Node* node_engine) : Glyph(node_engine){
  //---------------------------

  this->octreeManager = new ope::tree::Octree();

  this->name = "tree";
  this->is_permanent = true;
  this->is_visible = false;
  this->color = vec4(1, 1, 1, 0.7);
  this->level = 6;
  this->type = dat::object::glyph::TREE;

  //---------------------------
}
Tree::~Tree(){}

//Main function
void Tree::create(){
  //---------------------------

  //Create glyph
  data.name = "tree::data";
  data.width = 2;
  data.is_visible = is_visible;
  data.topology.type = utl::topology::LINE;
  data.unicolor = color;

  this->init();

  //---------------------------
}
void Tree::update_glyph(utl::type::Data* data){
  //---------------------------


  //---------------------------
}

}
