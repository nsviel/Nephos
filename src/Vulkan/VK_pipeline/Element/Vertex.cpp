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
void Vertex::pipeline_vertex_description(vk::structure::Pipeline* pipeline){
  //---------------------------

  this->single_vertex_attribut(pipeline);
  this->flow_vertex_binding(pipeline);

  //---------------------------
}

//Subfunction
void Vertex::single_vertex_attribut(vk::structure::Pipeline* pipeline){
  pipeline->element.vec_attribut_info.clear();
  //---------------------------

  for(auto& attribut : pipeline->info.vec_attribut){
    VkVertexInputAttributeDescription attribut_info{};

    switch(attribut){
      case vk::attribut::XYZ:{
        attribut_info.binding = 0;
        attribut_info.location = vk::attribut::location::XYZ;
        attribut_info.format = VK_FORMAT_R32G32B32_SFLOAT;
        attribut_info.offset = 0;
        break;
      }
      case vk::attribut::RGBA:{
        attribut_info.binding = 1;
        attribut_info.location = vk::attribut::location::RGBA;
        attribut_info.format = VK_FORMAT_R32G32B32A32_SFLOAT;
        attribut_info.offset = 0;
        break;
      }
      case vk::attribut::UV:{
        attribut_info.binding = 2;
        attribut_info.location = vk::attribut::location::UV;
        attribut_info.format = VK_FORMAT_R32G32_SFLOAT;
        attribut_info.offset = 0;
        break;
      }
      default:{
        std::cout<<"[error] pipeline vertex description"<<std::endl;
        break;
      }
    }

    pipeline->element.vec_attribut_info.push_back(attribut_info);
  }

  //---------------------------
}
void Vertex::flow_vertex_binding(vk::structure::Pipeline* pipeline){
  pipeline->element.vec_vertex_binding.clear();
  //---------------------------

  for(auto& attribut : pipeline->info.vec_attribut){
    VkVertexInputBindingDescription description{};

    switch(attribut){
      case vk::attribut::XYZ:{
        description.binding = 0;
        description.stride = sizeof(glm::vec3);
        description.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
        break;
      }
      case vk::attribut::RGBA:{
        description.binding = 1;
        description.stride = sizeof(glm::vec4);
        description.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
        break;
      }
      case vk::attribut::UV:{
        description.binding = 2;
        description.stride = sizeof(glm::vec2);
        description.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
        break;
      }
      default:{
        std::cout<<"[error] pipeline vertex description"<<std::endl;
        break;
      }
    }

    pipeline->element.vec_vertex_binding.push_back(description);
  }

  //---------------------------
}

}
