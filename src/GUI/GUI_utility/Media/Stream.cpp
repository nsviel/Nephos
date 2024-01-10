#include "Stream.h"

#include <GUI.h>
#include <Vulkan/Vulkan.h>
#include <Vulkan/VK_main/VK_texture.h>
#include <GUI/GUI_main/Render/Render.h>


namespace gui::media{

//Constructor / Destructor
Stream::Stream(GUI* gui){
  //---------------------------

  Render* gui_render = gui->get_rnd_tab();
  Vulkan* vulkan = gui_render->get_vulkan();
  this->vk_texture = vulkan->get_vk_texture();
  this->vk_image = nullptr;

  //---------------------------
}
Stream::~Stream(){}

//Main function
void Stream::draw_stream(eng::data::Image* image, ImVec2 image_size){
  //---------------------------

  if(!image->data.empty()){
    this->convert_data_into_texture(image);
    this->render_image(image_size);
  }

  //---------------------------
}

//Subfunction
void Stream::convert_data_into_texture(eng::data::Image* image){
  //---------------------------

  if(vk_image == nullptr){
    vk_image = vk_texture->load_texture(image);
    VkDescriptorSet descriptor  = ImGui_ImplVulkan_AddTexture(vk_image->sampler, vk_image->view, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
    this->texture = reinterpret_cast<ImTextureID>(descriptor);
  }else{
    vk_image->data = image->data;
    vk_texture->update_texture(vk_image);
  }

  //---------------------------
}
void Stream::render_image(ImVec2& image_size){
  //---------------------------

  ImGui::Image(texture, image_size);

  //---------------------------
}


}
