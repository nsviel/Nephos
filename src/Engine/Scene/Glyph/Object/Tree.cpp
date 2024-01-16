#include "Tree.h"

#include <Utility/Function/Math/fct_math.h>


namespace glyph::object{

//Constructor / destructor
Tree::Tree(Engine* engine) : Glyph(engine){
  //---------------------------

  this->octreeManager = new eng::ope::Octree();

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
  entity::Object* object = new entity::Object(engine);
  object->data->draw_line_width = 2;
  object->data->is_visible = is_visible;
  object->data->draw_type_name = "line";
  object->data->unicolor = color;
  this->vec_data.push_back(object);

  //---------------------------
}
void Tree::update_glyph(entity::Entity* entity){
  //---------------------------

  if(entity::Object* object = dynamic_cast<entity::Object*>(entity)){
    if(is_visible){
      //octreeManager->create_octree(cloud, level);
      vec_data[0]->data->xyz = object->data->xyz;
    }
  }

  //---------------------------
}

}
