#include "Mesh.h"
#include "Structure.h"

#include <Utility/Namespace.h>
#include <Data/Namespace.h>
#include <gltf/tiny_gltf.h>
#include <image/stb_image.h>


namespace fmt::gltf{

//Constructor / Destructor
Mesh::Mesh(){
  //---------------------------


  //---------------------------
}
Mesh::~Mesh(){}

//Main function
void Mesh::parse_meshes(fmt::gltf::Structure& tinygltf, std::shared_ptr<utl::base::Data> data){
  //---------------------------

  //Meshes
  for(auto& mesh : tinygltf.model.meshes){
    tinygltf.mesh = mesh;

    this->parse_mesh(tinygltf, data);
  }

  //---------------------------
}
void Mesh::parse_mesh(fmt::gltf::Structure& tinygltf, std::shared_ptr<utl::base::Data> data){
  //---------------------------

  // Iterate over each primitive in the mesh
  for (auto& primitive : tinygltf.mesh.primitives) {
    tinygltf.primitive = primitive;

    this->parse_primitive_mode(tinygltf, data);
    this->parse_primitive_xyz(tinygltf, data);
    this->parse_primitive_rgb(tinygltf, data);
    this->parse_primitive_idx(tinygltf, data);
    this->parse_primitive_tex(tinygltf, data);
  }

  //---------------------------
}

//Subfunction
void Mesh::parse_primitive_xyz(fmt::gltf::Structure& tinygltf, std::shared_ptr<utl::base::Data> data){
  data->xyz.clear();
  //---------------------------

  // Extract position data (XYZ)
  const auto& xyz_it = tinygltf.model.accessors[tinygltf.primitive.attributes.at("POSITION")];
  const auto& xyz_view = tinygltf.model.bufferViews[xyz_it.bufferView];
  const auto& xyz_buffer = tinygltf.model.buffers[xyz_view.buffer];

  const float* xyz_data = reinterpret_cast<const float*>(&xyz_buffer.data[xyz_view.byteOffset]);
  size_t xyz_size = xyz_it.count;

  for(int i=0; i<xyz_size; i++){
    float x = xyz_data[i * 3 + 0];
    float y = xyz_data[i * 3 + 1];
    float z = xyz_data[i * 3 + 2];
    data->xyz.push_back(glm::vec3(x, y ,z));
  }

  //---------------------------
}
void Mesh::parse_primitive_rgb(fmt::gltf::Structure& tinygltf, std::shared_ptr<utl::base::Data> data){
  data->rgb.clear();
  //---------------------------

  // Extract color data (RGB)
  if ( tinygltf.primitive.attributes.find("COLOR_0") != tinygltf.primitive.attributes.end()) {
    const auto& rgb_it =  tinygltf.model.accessors[ tinygltf.primitive.attributes.at("COLOR_0")];
    const auto& rgb_view =  tinygltf.model.bufferViews[rgb_it.bufferView];
    const auto& rgb_buffer =  tinygltf.model.buffers[rgb_view.buffer];

    const float* rgb_data = reinterpret_cast<const float*>(&rgb_buffer.data[rgb_view.byteOffset]);
    size_t rgb_size = rgb_it.count;

    for(int i=0; i<rgb_size; i++){
      float r = rgb_data[i * 3 + 0];
      float g = rgb_data[i * 3 + 1];
      float b = rgb_data[i * 3 + 2];
      data->rgb.push_back(glm::vec3(r, g, b));
    }
  }

  //---------------------------
}
void Mesh::parse_primitive_idx(fmt::gltf::Structure& tinygltf, std::shared_ptr<utl::base::Data> data){
  data->idx.clear();
  //---------------------------

  // Extract indices and reorder XYZ
  if (tinygltf.primitive.indices > -1) {
    const auto& idx_it =  tinygltf.model.accessors[ tinygltf.primitive.indices];
    const auto& idx_view =  tinygltf.model.bufferViews[idx_it.bufferView];
    const auto& idx_buffer =  tinygltf.model.buffers[idx_view.buffer];

    const unsigned int* idx_data = reinterpret_cast<const unsigned int*>(&idx_buffer.data[idx_view.byteOffset]);
    size_t idx_size = idx_it.count;

    //Indexed xyz
    for (size_t i = 0; i < idx_size; ++i) {
      data->idx.push_back(idx_data[i]);
    }

    //Indexed xyz
    std::vector<glm::vec3> vec_xyz;
    for (size_t i = 0; i < idx_size; ++i) {
      unsigned int index = data->idx[i];
      vec_xyz.push_back(data->xyz[index]);
    }
    data->xyz = vec_xyz;

    //Indexed rgb
    std::vector<glm::vec3> vec_rgb;
    if(vec_rgb.size() != 0)
    for (size_t i = 0; i < idx_size; ++i) {
      unsigned int index = data->idx[i];
      vec_rgb.push_back(data->rgb[index]);
    }
    data->rgb = vec_rgb;
  }

  //---------------------------
}
void Mesh::parse_primitive_tex(fmt::gltf::Structure& tinygltf, std::shared_ptr<utl::base::Data> data){
  //---------------------------

  if (tinygltf.primitive.material >= 0) {
    const auto& material = tinygltf.model.materials[tinygltf.primitive.material];

    // Check for base color texture
    if (material.pbrMetallicRoughness.baseColorTexture.index >= 0) {
      const auto& tex_idx = material.pbrMetallicRoughness.baseColorTexture.index;
      const auto& texture = tinygltf.model.textures[tex_idx];
      const auto& image = tinygltf.model.images[texture.source];

      if (image.uri.empty()) {
        // Image is embedded in the buffers
        if (image.bufferView >= 0) {
          const auto& buffer_view = tinygltf.model.bufferViews[image.bufferView];
          const auto& buffer = tinygltf.model.buffers[buffer_view.buffer];

          // Extract image data from the buffer (embedded)
          size_t offset = buffer_view.byteOffset;
          size_t length = buffer_view.byteLength;

          std::vector<uint8_t> image_data(buffer.data.begin() + offset, buffer.data.begin() + offset + length);

          // Use stb_image to decode the raw binary image data
          int width, height, channels;
          unsigned char* img_data = stbi_load_from_memory(image_data.data(), image_data.size(), &width, &height, &channels, STBI_rgb_alpha);

          if (img_data) {
            // Store the image as a vector<uint8_t>
            std::vector<uint8_t> final_image_data(img_data, img_data + (width * height * 4));  // RGBA

            std::shared_ptr<utl::base::Image> texture = std::make_shared<utl::base::Image>();
            texture->width = width;
            texture->height = height;
            texture->size = width * height * 4;
            texture->data = final_image_data;
            data->texture = texture;

            // Optionally, free image data after use
            stbi_image_free(img_data);
          }
        }
      }

    }
  }

  //---------------------------
}
void Mesh::parse_primitive_mode(fmt::gltf::Structure& tinygltf, std::shared_ptr<utl::base::Data> data){
  //---------------------------

  switch (tinygltf.primitive.mode) {
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
