#include "Tree.h"

#include <UTL_function/fct_math.h>
#include <ENG_operation/Color/Color.h>
#include <ENG_operation/Tree/Octree.h>


//Constructor / destructor
Tree::Tree(){
  //---------------------------

  this->octreeManager = new Octree();

  this->name = "tree";
  this->is_visible = false;
  this->tree_color = vec4(1, 1, 1, 0.7);
  this->tree_level = 6;

  //---------------------------
}
Tree::~Tree(){}

data::Glyph* Tree::create_glyph(Object* object){
  data::Glyph* tree = new data::Glyph();
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
void Tree::update_tree(Object* object, data::Glyph* tree){
  //---------------------------

  if(is_visible){
    //octreeManager->create_octree(cloud, tree_level);
    tree->xyz = glyph->xyz;
  }

  //---------------------------
}
