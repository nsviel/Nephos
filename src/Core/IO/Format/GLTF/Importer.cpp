#include "Importer.h"
#include "Mesh.h"
#include "Structure.h"

#include <Utility/Namespace.h>
#include <Data/Namespace.h>
#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <gltf/tiny_gltf.h>


namespace fmt::gltf{

//Constructor / Destructor
Importer::Importer(){
  //---------------------------

  this->gltf_mesh = new fmt::gltf::Mesh();

  this->format.ascii = ".gltf";
  this->format.binary = ".glb";

  //---------------------------
}
Importer::~Importer(){}

//Main function
std::shared_ptr<utl::base::Element> Importer::import(utl::base::Path path){
  utl::base::Element element;
  //---------------------------

  //Init
  std::shared_ptr<dat::base::Object> object = std::make_shared<dat::base::Object>();
  object->name = utl::path::get_name_from_path(path.build());
  object->data->name = utl::path::get_name_from_path(path.build());
  object->data->path = path;
  object->data->path.format = format.ascii;
  object->data->topology.type = utl::topology::TRIANGLE;

  //Model
  fmt::gltf::Structure tinygltf;
  if(path.format == ".gltf"){
    this->load_gltf(path.build(), tinygltf.model);
  }else if(path.format == ".glb"){
    this->load_glb(path.build(), tinygltf.model);
  }

  //Meshes
  for(auto& mesh : tinygltf.model.meshes){
    tinygltf.mesh = mesh;

    gltf_mesh->parse_mesh(tinygltf, object->data);
  }

  //---------------------------
  return object;
}

//Subfunction
void Importer::load_gltf(std::string path, tinygltf::Model& model){
  //---------------------------

  tinygltf::TinyGLTF loader;
  std::string err;
  std::string warn;

  bool ret = loader.LoadASCIIFromFile(&model, &err, &warn, path);
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
void Importer::load_glb(std::string path, tinygltf::Model& model){
  //---------------------------

  tinygltf::TinyGLTF loader;
  std::string err;
  std::string warn;

  bool ret = loader.LoadBinaryFromFile(&model, &err, &warn, path);
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
void Importer::info_model(tinygltf::Model& model){
  //---------------------------

  std::cout << "Model Characteristics:" << std::endl;

  // Iterate over each mesh in the model
  for (const auto& mesh : model.meshes) {
    std::cout << "Mesh Name: " << mesh.name << std::endl;

    // Iterate over each primitive in the mesh
    for (size_t i = 0; i < mesh.primitives.size(); ++i) {
      const auto& primitive = mesh.primitives[i];

      // Display primitive index (optional)
      std::cout << "  Primitive " << i << ": ";

      // Check if a name exists for the primitive and print it
      if (primitive.attributes.find("POSITION") != primitive.attributes.end()) {
        std::cout << "Has Position Attribute";
      }

      if (primitive.attributes.find("COLOR_0") != primitive.attributes.end()) {
        std::cout << ", Has Color Attribute";
      }

      if (primitive.indices > -1) {
        std::cout << ", Has Indices Attribute";
      }

      std::cout << std::endl;
    }
  }

  //---------------------------
}

}
