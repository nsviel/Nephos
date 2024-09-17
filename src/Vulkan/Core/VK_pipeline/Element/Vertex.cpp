#include "Vertex.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::pipeline{

//Constructor / Destructor
Vertex::Vertex(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;

  //---------------------------
}
Vertex::~Vertex(){}

//Main function
void Vertex::pipeline_vertex_description(vk::structure::Pipeline& pipeline){
  pipeline.element.vec_vertex_attribute.clear();
  pipeline.element.vec_vertex_binding.clear();
  //---------------------------

  for(auto& attribut : pipeline.info.vec_attribut){
    switch(attribut){
      case vk::attribut::XYZ:{
        this->add_vertex_xyz(pipeline);
        break;
      }
      case vk::attribut::RGBA:{
        this->add_vertex_rgba(pipeline);
        break;
      }
      case vk::attribut::UV:{
        this->add_vertex_uv(pipeline);
        break;
      }
      default:{
        std::cout<<"[error] pipeline vertex description"<<std::endl;
        break;
      }
    }
  }

  //---------------------------
}

//Subfunction
void Vertex::add_vertex_xyz(vk::structure::Pipeline& pipeline){
  //---------------------------

  //Vertex description
  VkVertexInputAttributeDescription attribute{};
  attribute.binding = vk::attribut::binding::XYZ;
  attribute.location = vk::attribut::location::XYZ;
  attribute.format = VK_FORMAT_R32G32B32_SFLOAT;
  attribute.offset = 0;
  pipeline.element.vec_vertex_attribute.push_back(attribute);

  //Vertex binding
  VkVertexInputBindingDescription description{};
  description.binding = 0;
  description.stride = sizeof(glm::vec3);
  description.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
  pipeline.element.vec_vertex_binding.push_back(description);

  //---------------------------
}
void Vertex::add_vertex_rgba(vk::structure::Pipeline& pipeline){
  //---------------------------

  //Vertex description
  VkVertexInputAttributeDescription attribute{};
  attribute.binding = vk::attribut::binding::RGBA;
  attribute.location = vk::attribut::location::RGBA;
  attribute.format = VK_FORMAT_R32G32B32A32_SFLOAT;
  attribute.offset = 0;
  pipeline.element.vec_vertex_attribute.push_back(attribute);

  //Vertex binding
  VkVertexInputBindingDescription description{};
  description.binding = 1;
  description.stride = sizeof(glm::vec4);
  description.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
  pipeline.element.vec_vertex_binding.push_back(description);

  //---------------------------
}
void Vertex::add_vertex_uv(vk::structure::Pipeline& pipeline){
  //---------------------------

  //Vertex description
  VkVertexInputAttributeDescription attribute{};
  attribute.binding = vk::attribut::binding::UV;
  attribute.location = vk::attribut::location::UV;
  attribute.format = VK_FORMAT_R32G32_SFLOAT;
  attribute.offset = 0;
  pipeline.element.vec_vertex_attribute.push_back(attribute);

  //Vertex binding
  VkVertexInputBindingDescription description{};
  description.binding = 2;
  description.stride = sizeof(glm::vec2);
  description.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
  pipeline.element.vec_vertex_binding.push_back(description);

  //---------------------------
}

}
