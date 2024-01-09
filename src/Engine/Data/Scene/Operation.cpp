#include "Operation.h"


namespace eng::scene{

//Constructor / Destructor
Operation::Operation(eng::scene::Node* sce_node){
  //---------------------------

this->sce_database = sce_node->get_scene_database();

  //---------------------------
}
Operation::~Operation(){}

//Main function
void Operation::make_translation(){
  //---------------------------

  eng::data::Set* data_set = sce_database->get_data_set();
  eng::data::Set* set_scene = data_set->get_set("Scene");
  //ope_transform->make_translation((eng::data::Object*)set_scene->selected_entity, translation);

  //---------------------------
}



}
