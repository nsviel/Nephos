#include "Importer.h"

#include <Data/Namespace.h>
#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <gltf/tiny_gltf.h>


namespace fmt::gltf{

//Constructor / Destructor
Importer::Importer(){
  //---------------------------

  this->format.ascii = ".glb";

  //---------------------------
}
Importer::~Importer(){}

//Main function
std::shared_ptr<utl::base::Element> Importer::import(utl::base::Path path){
  //---------------------------

  //Init
  std::shared_ptr<dat::base::Object> object = std::make_shared<dat::base::Object>();
  object->name = utl::path::get_name_from_path(path.build());
  object->data->name = utl::path::get_name_from_path(path.build());
  object->data->path = path;
  object->data->path.format = format.ascii;
  object->data->topology.type = utl::topology::POINT;

  //Init
  this->load_file(path.build());

  //---------------------------
  return object;
}

//Subfunction
void Importer::load_file(std::string path){
  //---------------------------

  tinygltf::Model model;
  tinygltf::TinyGLTF loader;
  std::string err;
  std::string warn;

  bool ret = loader.LoadASCIIFromFile(&model, &err, &warn, path);
  //bool ret = loader.LoadBinaryFromFile(&model, &err, &warn, argv[1]); // for binary glTF(.glb)
  if(!warn.empty()){
    printf("Warn: %s\n", warn.c_str());
  }
  if(!err.empty()){
    printf("Err: %s\n", err.c_str());
  }
  if(!ret){
    printf("Failed to parse glTF\n");
  }

  //---------------------------
}

}
