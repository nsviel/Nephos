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
  if(vec_object.size() != 0) return;
  //---------------------------

  //Create glyph
  eng::data::Object* object = new eng::data::Object();
  object->name = "tree";
  object->draw_line_width = 2;
  object->is_visible = is_visible;
  object->draw_type_name = "line";
  object->is_permanent = true;
  object->unicolor = color;
  this->vec_object.push_back(object);

  //---------------------------
}
void Tree::update(eng::data::Entity* entity){
  //---------------------------

  if(eng::data::Object* object = dynamic_cast<eng::data::Object*>(entity)){
    if(is_visible){
      //octreeManager->create_octree(cloud, level);
      vec_object[0]->xyz = object->xyz;
    }
  }

  //---------------------------
}

}
