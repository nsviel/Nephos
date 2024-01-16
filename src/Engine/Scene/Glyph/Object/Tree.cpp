#include "Tree.h"

#include <Utility/Function/Math/fct_math.h>


namespace glyph::object{

//Constructor / destructor
Tree::Tree(Engine* engine) : Glyph(engine){
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
  entity::Object* object = new entity::Object(engine);
  object->name = "tree";
  object->data->draw_line_width = 2;
  object->is_visible = is_visible;
  object->draw_type_name = "line";
  object->is_permanent = true;
  object->unicolor = color;
  this->vec_object.push_back(object);

  //---------------------------
}
void Tree::update_glyph(entity::Entity* entity){
  //---------------------------

  if(entity::Object* object = dynamic_cast<entity::Object*>(entity)){
    if(is_visible){
      //octreeManager->create_octree(cloud, level);
      vec_object[0]->data->xyz = object->data->xyz;
    }
  }

  //---------------------------
}

}
