#include "Tree.h"

#include <Utility/Function/Math/fct_math.h>


namespace glyph::object{

//Constructor / destructor
Tree::Tree(){
  //---------------------------

  this->octreeManager = new eng::ope::Octree();

  this->name = "tree";
  this->is_visible = false;
  this->tree_color = vec4(1, 1, 1, 0.7);
  this->tree_level = 6;

  //---------------------------
}
Tree::~Tree(){}

//Main function
eng::data::Object* Tree::create(eng::data::Object* object){
  eng::data::Object* tree = new eng::data::Object();
  //---------------------------

  //Create glyph
  tree->name = "tree";
  tree->draw_line_width = 2;
  tree->is_visible = is_visible;
  tree->draw_type_name = "line";
  tree->is_permanent = true;
  tree->unicolor = tree_color;

  //---------------------------
  return tree;
}
void Tree::update(eng::data::Object* object, eng::data::Object* tree){
  //---------------------------

  if(is_visible){
    //octreeManager->create_octree(cloud, tree_level);
    tree->xyz = glyph->xyz;
  }

  //---------------------------
}

}
