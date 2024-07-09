#include "Data.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::pipeline{

//Constructor / Destructor
Data::Data(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;

  //---------------------------
}
Data::~Data(){}

//Main function
void Data::pipeline_data_description(vk::structure::Pipeline* pipeline){
  //---------------------------

  this->pipeline_binding_description(pipeline);
  this->pipeline_attribut_description(pipeline);

  //---------------------------
}

//Subfunction
void Data::pipeline_attribut_description(vk::structure::Pipeline* pipeline){
  std::vector<VkVertexInputAttributeDescription> attribut_description;
  //---------------------------

  std::vector<std::string>& vec_data_name = pipeline->info.vec_data_name;
  for(int i=0; i<vec_data_name.size(); i++){
    VkVertexInputAttributeDescription attribut{};

    if(vec_data_name[i] == "location"){
      attribut.binding = 0;
      attribut.location = 0;
      attribut.format = VK_FORMAT_R32G32B32_SFLOAT;
      attribut.offset = 0;
    }
    else if(vec_data_name[i] == "color"){
      attribut.binding = 1;
      attribut.location = 1;
      attribut.format = VK_FORMAT_R32G32B32A32_SFLOAT;
      attribut.offset = 0;
    }
    else if(vec_data_name[i] == "tex_coord"){
      attribut.binding = 2;
      attribut.location = 4;
      attribut.format = VK_FORMAT_R32G32_SFLOAT;
      attribut.offset = 0;
    }
    else{
      std::cout<<"[error] data description"<<std::endl;
      break;
    }

    attribut_description.push_back(attribut);
  }

  //---------------------------
  pipeline->element.attribut_description = attribut_description;
}
void Data::pipeline_binding_description(vk::structure::Pipeline* pipeline){
  std::vector<VkVertexInputBindingDescription> data_description;
  //---------------------------

  std::vector<std::string>& vec_data_name = pipeline->info.vec_data_name;
  for(int i=0; i<vec_data_name.size(); i++){
    VkVertexInputBindingDescription description{};

    if(vec_data_name[i] == "location"){
      description.binding = 0;
      description.stride = sizeof(glm::vec3);
      description.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    }
    else if(vec_data_name[i] == "color"){
      description.binding = 1;
      description.stride = sizeof(glm::vec4);
      description.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    }
    else if(vec_data_name[i] == "tex_coord"){
      description.binding = 2;
      description.stride = sizeof(glm::vec2);
      description.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    }
    else{
      std::cout<<"[error] data description"<<std::endl;
      break;
    }

    data_description.push_back(description);
  }

  //---------------------------
  pipeline->element.data_description = data_description;
}

}
