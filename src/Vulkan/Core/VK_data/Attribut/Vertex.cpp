#include "Vertex.h"

#include <Vulkan/Namespace.h>


namespace vk::data{

//Constructor / Destructor
Vertex::Vertex(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_fence = new vk::synchro::Fence(vk_struct);
  this->vk_semaphore = new vk::synchro::Semaphore(vk_struct);

  //---------------------------
}
Vertex::~Vertex(){}

//Main function
void Vertex::build_vertex(vk::structure::Object& vk_object){
  utl::base::Data& data = *vk_object.data;
  //---------------------------

  //XYZ vertex
  if(!data.xyz.empty()){
    vk::structure::Vertex vertex;
    vertex.channel = sizeof(glm::vec3);
    vertex.binding = vk::attribut::binding::XYZ;
    vertex.size = data.xyz.size();
    vertex.size_max = std::max(data.size_max, vertex.channel * vertex.size);
    vk_object.map_vertex[vk::vertex::XYZ] = vertex;
  }

  //RGBA vertex
  if(!data.rgba.empty()){
    vk::structure::Vertex vertex;
    vertex.channel = sizeof(glm::vec4);
    vertex.binding = vk::attribut::binding::RGBA;
    vertex.size = data.rgba.size();
    vertex.size_max = std::max(data.size_max, vertex.channel * vertex.size);
    vk_object.map_vertex[vk::vertex::RGBA] = vertex;
  }

  //UV vertex
  if(!data.uv.empty()){
    vk::structure::Vertex vertex;
    vertex.channel = sizeof(glm::vec2);
    vertex.binding = vk::attribut::binding::UV;
    vertex.size = data.uv.size();
    vertex.size_max = std::max(data.size_max, vertex.channel * vertex.size);
    vk_object.map_vertex[vk::vertex::UV] = vertex;
  }

  //---------------------------
}

//Subfunction
void Vertex::cmd_draw_vertex(VkCommandBuffer& command_buffer, vk::structure::Object& vk_object){
  //---------------------------
  
  for(auto& [type, vertex] : vk_object.map_vertex){
    if(vertex.buffer.vbo == VK_NULL_HANDLE) continue;
    VkDeviceSize offsets[] = {0};
    vkCmdBindVertexBuffers(command_buffer, vertex.binding, 1, &vertex.buffer.vbo, offsets);
  }

  vkCmdDraw(command_buffer, vk_object.data->xyz.size(), 1, 0, 0);

  //---------------------------
}
void Vertex::cmd_line_with(VkCommandBuffer& command_buffer, vk::structure::Object& vk_object){
  //---------------------------

  vkCmdSetLineWidth(command_buffer, vk_object.data->width);

  //---------------------------
}

}
