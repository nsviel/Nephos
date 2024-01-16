#include "Glyph.h"

#include <Engine/Engine.h>
#include <Engine/Camera/Namespace.h>
#include <Utility/Function/Math/fct_math.h>


namespace entity{

//Constructor / Destructor
Glyph::Glyph(Engine* engine){
  //---------------------------

  this->engine = engine;
  this->color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
  this->is_visible = true;
  this->type = "Glyph";

  //---------------------------
}
Glyph::~Glyph(){}

//Main function
void Glyph::update_entity(){
  eng::camera::Node* node_camera = engine->get_node_camera();
  eng::camera::Control* cam_control = node_camera->get_camera_control();
  //----------------------------

  for(int i=0; i<vec_data.size(); i++){
    cam_control->compute_camera_mvp(vec_data[i]->data);
  }

  //----------------------------
}
void Glyph::visibility_entity(bool value){
  //---------------------------

  this->is_visible = value;
  for(int i=0; i<vec_data.size(); i++){
    entity::Object* object = vec_data[i];
    object->data->is_visible = value;
  }

  //---------------------------
}


}
