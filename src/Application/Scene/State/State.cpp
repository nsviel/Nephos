#include "State.h"

#include <Core/Namespace.h>
#include <Scene/Namespace.h>
#include <Data/Namespace.h>
#include <Utility/Namespace.h>


namespace sce{

//Constructor / Destructor
State::State(sce::Node* node_scene){
  //---------------------------

  core::Node* node_core = node_scene->get_node_core();
  dat::Node* node_data = node_core->get_node_data();
  dat::gph::Node* node_graph = node_data->get_node_graph();

  this->dat_graph = node_graph->get_gph_graph();

  //---------------------------
}
State::~State(){}

//Main function
void State::export_json(){
  std::string path = "";
  //---------------------------


  sce::structure::Scene sce_struct;
  sce_struct.name = "first scene";


std::shared_ptr<dat::base::Set> set_main = dat_graph->get_set_main();
this->populate_scene(sce_struct, set_main);




  // Create a JSON object to store the matrix values
  nlohmann::json j;
  j["name"] = sce_struct.name;

  // Write the JSON object to the file
  std::ofstream file(path);
  if(file.is_open()){
    file << j.dump(4); // Use dump(4) for pretty printing with an indentation of 4 spaces
    file.close();
  }else{
    std::cerr << "Failed to open the file for writing." << std::endl;
  }

  //---------------------------
}
void State::populate_scene(sce::structure::Scene& sce_struct, std::shared_ptr<dat::base::Set> set){
  //---------------------------

  // Process entities within the current set
  for(auto& entity : set->list_entity){
    sce::structure::Object object;
    object.name = entity->data->name;
    object.position = entity->pose->translation.coeff;
    object.rotation = entity->pose->rotation.coeff;
    object.scale = entity->pose->scale.coeff;

    //sce_struct.vec_object.push_back(object);
  }

  // Recursively process nested sets
  for(auto& subset : set->list_subset){
    this->populate_scene(sce_struct, subset);
  }

  //---------------------------
}

}
