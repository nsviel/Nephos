#include "Stream.h"

#include <Vulkan/Namespace.h>
#include <GUI/Namespace.h>


namespace vk::render::gui{

//Constructor / Destructor
Stream::Stream(vk::Node* node_vulkan){
  //---------------------------

  this->vk_texture = node_vulkan->get_vk_texture();
  this->texture = nullptr;
  this->imgui_texture = 0;

  //---------------------------
}
Stream::~Stream(){}

//Main function
void Stream::draw_stream(utl::media::Image* utl_image, ImVec2 size){
  if(utl_image->size == 0) return;
  //---------------------------

  this->convert_data_into_texture(utl_image, size);
  this->render_image(size);

  //---------------------------
}

//Subfunction
void Stream::convert_data_into_texture(utl::media::Image* utl_image, ImVec2& size){
  //---------------------------

  if(texture == nullptr){
    //Load texture into vulkan
    texture = vk_texture->load_texture(utl_image);
    if(texture == nullptr) return;

    //Retrieve descriptor from vulkan texture
    VkDescriptorSet descriptor  = ImGui_ImplVulkan_AddTexture(texture->vk_image.sampler, texture->vk_image.view, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
    this->imgui_texture = reinterpret_cast<ImTextureID>(descriptor);
  }else if(utl_image->new_data){
    //update texture data
    vk_texture->update_texture(texture);
    utl_image->new_data = false;
  }

  //---------------------------
}
void Stream::render_image(ImVec2& size){
  if(imgui_texture == 0) return;
  //---------------------------

  ImGui::Image(imgui_texture, size);

  //---------------------------
}


}
