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
  std::vector<VkVertexInputAttributeDescription> vec_vertex_attribut;
  //---------------------------

  std::vector<vk::pipeline::Attribut>& vec_attribut = pipeline->info.vec_attribut;
  for(int i=0; i<vec_attribut.size(); i++){
    VkVertexInputAttributeDescription attribut{};

    switch(vec_attribut[i]){
      case vk::pipeline::XYZ:{
        attribut.binding = 0;
        attribut.location = 0;
        attribut.format = VK_FORMAT_R32G32B32_SFLOAT;
        attribut.offset = 0;
        break;
      }
      case vk::pipeline::RGBA:{
        attribut.binding = 1;
        attribut.location = 1;
        attribut.format = VK_FORMAT_R32G32B32A32_SFLOAT;
        attribut.offset = 0;
        break;
      }
      case vk::pipeline::UV:{
        attribut.binding = 2;
        attribut.location = 4;
        attribut.format = VK_FORMAT_R32G32_SFLOAT;
        attribut.offset = 0;
        break;
      }
      default:{
        std::cout<<"[error] pipeline vertex description"<<std::endl;
        break;
      }
    }

    vec_vertex_attribut.push_back(attribut);
  }

  //---------------------------
  pipeline->element.vec_vertex_attribut = vec_vertex_attribut;
}
void Vertex::flow_vertex_binding(vk::structure::Pipeline* pipeline){
  std::vector<VkVertexInputBindingDescription> vec_vertex_binding;
  //---------------------------

  std::vector<vk::pipeline::Attribut>& vec_attribut = pipeline->info.vec_attribut;
  for(int i=0; i<vec_attribut.size(); i++){
    VkVertexInputBindingDescription description{};

    switch(vec_attribut[i]){
      case vk::pipeline::XYZ:{
        description.binding = 0;
        description.stride = sizeof(glm::vec3);
        description.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
        break;
      }
      case vk::pipeline::RGBA:{
        description.binding = 1;
        description.stride = sizeof(glm::vec4);
        description.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
        break;
      }
      case vk::pipeline::UV:{
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

    vec_vertex_binding.push_back(description);
  }

  //---------------------------
  pipeline->element.vec_vertex_binding = vec_vertex_binding;
}

}
