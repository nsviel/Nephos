#include "Import.h"

#include <Scene/Namespace.h>
#include <Core/Namespace.h>
#include <IO/Namespace.h>


namespace sce{

//Constructor / Destructor
Import::Import(sce::Node* node_scene){
  //---------------------------

  core::Node* node_core = node_scene->get_node_core();
  io::Node* node_io = node_core->get_node_io();
  io::imp::Node* node_importer = node_io->get_node_importer();

  this->sce_struct = node_scene->get_sce_struct();
  this->io_loader = node_importer->get_io_loader();
  this->io_struct = node_importer->get_io_struct();

  //---------------------------
}
Import::~Import(){}

//Main function
void Import::init(){
  //---------------------------

  std::string name = "base.json";

  this->load_objects(sce_struct->path + name);

  //---------------------------
}
void Import::import_json(){
  //---------------------------

  std::string name = "base.json";

  this->load_objects(sce_struct->path + name);

  //---------------------------
}

//Subfunction
void Import::load_objects(std::string path){
  //---------------------------

  // Read the JSON file
  std::ifstream file(path);
  if (!file.is_open()) {
    throw std::runtime_error("Could not open file: " + path);
  }

  nlohmann::json j;
  file >> j;
  file.close();

  // Check if the "objects" key exists and is an array
  if (j.contains("objects") && j["objects"].is_array()) {
    for (const auto& object : j["objects"]) {
      if (object.contains("path") && object["path"].is_string()) {
        std::string path = object["path"].get<std::string>();
        io_loader->load_object(path);
      }
    }
  }

  //---------------------------
}

}
