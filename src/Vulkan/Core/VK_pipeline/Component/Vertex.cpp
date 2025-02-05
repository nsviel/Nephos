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
  pipeline.component.vec_vertex_attribute.clear();
  pipeline.component.vec_vertex_binding.clear();
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
  this->info_pipeline_vertex(pipeline);
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
  pipeline.component.vec_vertex_attribute.push_back(attribute);

  //Vertex binding
  VkVertexInputBindingDescription description{};
  description.binding = vk::attribut::binding::XYZ;
  description.stride = sizeof(glm::vec3);
  description.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
  pipeline.component.vec_vertex_binding.push_back(description);

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
  pipeline.component.vec_vertex_attribute.push_back(attribute);

  //Vertex binding
  VkVertexInputBindingDescription description{};
  description.binding = vk::attribut::binding::RGBA;
  description.stride = sizeof(glm::vec4);
  description.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
  pipeline.component.vec_vertex_binding.push_back(description);

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
  pipeline.component.vec_vertex_attribute.push_back(attribute);

  //Vertex binding
  VkVertexInputBindingDescription description{};
  description.binding = vk::attribut::binding::UV;
  description.stride = sizeof(glm::vec2);
  description.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
  pipeline.component.vec_vertex_binding.push_back(description);

  //---------------------------
}
void Vertex::info_pipeline_vertex(vk::structure::Pipeline& pipeline){
  //---------------------------

  VkPipelineVertexInputStateCreateInfo vertex{};
  vertex.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
  vertex.vertexBindingDescriptionCount = static_cast<uint32_t>(pipeline.component.vec_vertex_binding.size());
  vertex.vertexAttributeDescriptionCount = static_cast<uint32_t>(pipeline.component.vec_vertex_attribute.size());
  vertex.pVertexBindingDescriptions = pipeline.component.vec_vertex_binding.data();
  vertex.pVertexAttributeDescriptions = pipeline.component.vec_vertex_attribute.data();

  //---------------------------
  pipeline.component.vertex = vertex;
}

}
