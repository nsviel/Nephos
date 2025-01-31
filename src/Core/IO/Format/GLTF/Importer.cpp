#include "Importer.h"

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
  tinygltf::Model model;
  if(path.format == ".gltf"){
    this->load_gltf(path.build(), model);
  }else if(path.format == ".glb"){
    this->load_glb(path.build(), model);
  }
  
  //Meshes
  this->parse_meshes(model, object->data);

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
void Importer::parse_meshes(tinygltf::Model& model, std::shared_ptr<utl::base::Data> data){
  std::vector<glm::vec3> vec_xyz;
  std::vector<glm::vec3> vec_rgb;
  std::vector<glm::vec3> idx_xyz;
  std::vector<glm::vec3> idx_rgb;
  //---------------------------

  //Meshes
  for(auto& mesh : model.meshes){
    // Iterate over each primitive in the mesh
    for (const auto& primitive : mesh.primitives) {

      // Extract position data (XYZ)
      const auto& xyz_it = model.accessors[primitive.attributes.at("POSITION")];
      const auto& xyz_view = model.bufferViews[xyz_it.bufferView];
      const auto& xyz_buffer = model.buffers[xyz_view.buffer];

      const float* xyz_data = reinterpret_cast<const float*>(&xyz_buffer.data[xyz_view.byteOffset]);
      size_t numVertices = xyz_it.count;

      std::cout << "Positions (XYZ):\n";
      for (size_t i = 0; i < numVertices; ++i) {
        float x = xyz_data[i * 3 + 0];
        float y = xyz_data[i * 3 + 1];
        float z = xyz_data[i * 3 + 2];
        vec_xyz.push_back(glm::vec3(x, y ,z));
      }

      // Extract color data (RGB)
      if (primitive.attributes.find("COLOR_0") != primitive.attributes.end()) {
        const auto& rgb_it = model.accessors[primitive.attributes.at("COLOR_0")];
        const auto& rgb_view = model.bufferViews[rgb_it.bufferView];
        const auto& rgb_buffer = model.buffers[rgb_view.buffer];

        const float* rgb_data = reinterpret_cast<const float*>(&rgb_buffer.data[rgb_view.byteOffset]);

        std::cout << "Colors (RGB):\n";
        for (size_t i = 0; i < numVertices; ++i) {
          float r = rgb_data[i * 3 + 0];
          float g = rgb_data[i * 3 + 1];
          float b = rgb_data[i * 3 + 2];
          vec_rgb.push_back(glm::vec3(r, g, b));
        }
      }

      // Extract indices and reorder XYZ
      if (primitive.indices > -1) {
        const auto& idx_it = model.accessors[primitive.indices];
        const auto& idx_view = model.bufferViews[idx_it.bufferView];
        const auto& idx_buffer = model.buffers[idx_view.buffer];

        const unsigned int* idx_data = reinterpret_cast<const unsigned int*>(&idx_buffer.data[idx_view.byteOffset]);
        size_t idx_size = idx_it.count;

        //Indexed xyz
        for (size_t i = 0; i < idx_size; ++i) {
          unsigned int index = idx_data[i];
          idx_xyz.push_back(vec_xyz[index]);
        }

        //Indexed rgb
        if(vec_rgb.size() != 0)
        for (size_t i = 0; i < idx_size; ++i) {
          unsigned int index = idx_data[i];
          idx_rgb.push_back(vec_rgb[index]);
        }
      }else{
        idx_xyz = vec_xyz;
        idx_rgb = vec_rgb;
      }

      // Retrieve texture information (if available)
      if (primitive.material >= 0) {
        const auto& material = model.materials[primitive.material];

        // Check for base color texture
        if (material.pbrMetallicRoughness.baseColorTexture.index >= 0) {
          const auto& textureIndex = material.pbrMetallicRoughness.baseColorTexture.index;
          const auto& texture = model.textures[textureIndex];
          const auto& image = model.images[texture.source];

          std::cout << "Texture found for mesh: " << mesh.name << std::endl;
          std::cout << "Texture: " << texture.name << ", Image: " << image.uri << std::endl;
        } else {
          std::cout << "No base color texture available for mesh: " << mesh.name << std::endl;
        }
      }

    }
  }

  data->xyz = idx_xyz;
  data->rgb = idx_rgb;

  //---------------------------
}
void Importer::parse_mode(int mode, std::shared_ptr<utl::base::Data> data){
  //---------------------------

  switch (mode) {
    case TINYGLTF_MODE_POINTS:{
      data->topology.type = utl::topology::POINT;
      break;
    }
    case TINYGLTF_MODE_LINE:{
      data->topology.type = utl::topology::LINE;
      break;
    }
    case TINYGLTF_MODE_LINE_STRIP:{
      data->topology.type = utl::topology::LINE_STRIP;
      break;
    }
    case TINYGLTF_MODE_TRIANGLES:{
      data->topology.type = utl::topology::TRIANGLE;
      break;
    }
    case TINYGLTF_MODE_TRIANGLE_STRIP:{
      data->topology.type = utl::topology::TRIANGLE_STRIP;
      break;
    }
    case TINYGLTF_MODE_TRIANGLE_FAN:{
      data->topology.type = utl::topology::TRIANGLE_FAN;
      break;
    }
  }

  //---------------------------
}

}
