#include "Export.h"

#include <Core/Namespace.h>
#include <Scene/Namespace.h>
#include <Data/Namespace.h>
#include <Utility/Namespace.h>


namespace sce{

//Constructor / Destructor
Export::Export(sce::Node* node_scene){
  //---------------------------

  core::Node* node_core = node_scene->get_node_core();
  dat::Node* node_data = node_core->get_node_data();
  dat::gph::Node* node_graph = node_data->get_node_graph();

  this->sce_struct = node_scene->get_sce_struct();
  this->dat_graph = node_graph->get_gph_graph();

  //---------------------------
}
Export::~Export(){}

//Main function
void Export::export_json(){
  //---------------------------

  std::string name = "base.json";

  // Create a JSON object to store the matrix values
  std::shared_ptr<dat::base::Set> set_graph = dat_graph->get_set_graph();
  nlohmann::json j;
  j["name"] = name;
  this->populate_scene(j, set_graph);

  // Write the JSON object to the file
  std::ofstream file(sce_struct->path + name);
  if(file.is_open()){
    file << j.dump(4); // Use dump(4) for pretty printing with an indentation of 4 spaces
    file.close();
  }else{
    std::cerr << "Failed to open the file for writing." << std::endl;
  }

  //---------------------------
}

//Subfunction
void Export::populate_scene(nlohmann::json& j, std::shared_ptr<dat::base::Set> set){
  //---------------------------

  // Process entities within the current set
  for (auto& entity : set->list_entity) {
    nlohmann::json object;
    object["name"] = entity->data->name;
    object["path"] = entity->data->path.build();
    object["position"] = {entity->pose->translation.coeff.x, entity->pose->translation.coeff.y, entity->pose->translation.coeff.z};
    object["rotation"] = {entity->pose->rotation.coeff.x, entity->pose->rotation.coeff.y, entity->pose->rotation.coeff.z};
    object["scale"] = {entity->pose->scale.coeff.x, entity->pose->scale.coeff.y, entity->pose->scale.coeff.z};
    j["objects"].push_back(object);
  }

  // Recursively process nested sets
  for (auto& subset : set->list_subset) {
    this->populate_scene(j, subset);
  }

  //---------------------------
}

}
