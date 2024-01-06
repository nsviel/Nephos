#include "Tree.h"

#include <Utility/Function/Math/fct_math.h>


namespace glyph::object{

//Constructor / destructor
Tree::Tree(){
  //---------------------------

  this->octreeManager = new eng::ope::Octree();

  this->name = "tree";
  this->is_visible = false;
  this->color = vec4(1, 1, 1, 0.7);
  this->level = 6;

  //---------------------------
}
Tree::~Tree(){}

//Main function
void Tree::create(){
  //---------------------------

  //Create glyph
  data = new eng::data::Object();
  data->name = "tree";
  data->draw_line_width = 2;
  data->is_visible = is_visible;
  data->draw_type_name = "line";
  data->is_permanent = true;
  data->unicolor = color;

  //---------------------------
}
void Tree::update(eng::data::Object* object){
  //---------------------------

  if(is_visible){
    //octreeManager->create_octree(cloud, level);
    data->xyz = object->xyz;
  }

  //---------------------------
}

}
