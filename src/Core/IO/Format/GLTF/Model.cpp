#include "Model.h"
#include "Structure.h"

#include <Utility/Namespace.h>
#include <Data/Namespace.h>
#include <gltf/tiny_gltf.h>


namespace fmt::gltf{

//Constructor / Destructor
Model::Model(){
  //---------------------------


  //---------------------------
}
Model::~Model(){}

//Main function
void Model::load_model(fmt::gltf::Structure& tinygltf, utl::base::Path path){
  //---------------------------

  if(path.format == ".gltf"){
    this->load_gltf(path.build(), tinygltf.model);
  }else if(path.format == ".glb"){
    this->load_glb(path.build(), tinygltf.model);
  }

  //---------------------------
}
void Model::info_model(tinygltf::Model& model){
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

//Subfunction
void Model::load_gltf(std::string path, tinygltf::Model& model){
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
void Model::load_glb(std::string path, tinygltf::Model& model){
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

}
