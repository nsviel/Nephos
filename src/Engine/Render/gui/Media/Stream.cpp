#include "Stream.h"

#include <Engine/Node.h>
#include <Vulkan/Node.h>
#include <Vulkan/VK_main/Texture.h>
#include <Vulkan/VK_struct/Namespace.h>
#include <GUI/Namespace.h>


namespace eng::render::gui{

//Constructor / Destructor
Stream::Stream(eng::Node* engine){
  //---------------------------

  vk::Node* vulkan = engine->get_eng_vulkan();
  this->vk_texture = vulkan->get_vk_texture();
  this->vk_image = nullptr;

  //---------------------------
}
Stream::~Stream(){}

//Main function
void Stream::draw_stream(utl::media::Image* utl_image, ImVec2 size){
  //---------------------------

  if(!utl_image->buffer.empty()){
    this->convert_data_into_texture(utl_image);
    this->render_image(size);
  }

  //---------------------------
}

//Subfunction
void Stream::convert_data_into_texture(utl::media::Image* utl_image){
  //---------------------------

  if(vk_image == nullptr){
    vk_image = vk_texture->load_texture(utl_image);
    VkDescriptorSet descriptor  = ImGui_ImplVulkan_AddTexture(vk_image->sampler, vk_image->view, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
    this->texture = reinterpret_cast<ImTextureID>(descriptor);
  }else{
    vk_image->buffer = &utl_image->buffer;
    vk_texture->update_texture(vk_image);
  }

  //---------------------------
}
void Stream::render_image(ImVec2& size){
  //---------------------------

  ImGui::Image(texture, size);

  //---------------------------
}


}
