#include "Tree.h"

#include <Utility/Function/Math/fct_math.h>
#include <Engine/ENG_operation/Color/Color.h>
#include <Engine/ENG_operation/Tree/Octree.h>


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

eng::structure::Glyph* Tree::create_glyph(eng::structure::Object* object){
  eng::structure::Glyph* tree = new eng::structure::Glyph();
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
void Tree::update_tree(eng::structure::Object* object, eng::structure::Glyph* tree){
  //---------------------------

  if(is_visible){
    //octreeManager->create_octree(cloud, tree_level);
    tree->xyz = glyph->xyz;
  }

  //---------------------------
}
