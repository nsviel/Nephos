#include "GUI_stream.h"

#include <GUI.h>
#include <Vulkan.h>
#include <VK_main/VK_texture.h>
#include <GUI_main/GUI_render/GUI_render.h>



//Constructor / Destructor
GUI_stream::GUI_stream(GUI* gui){
  //---------------------------

  GUI_render* gui_render = gui->get_rnd_tab();
  Vulkan* vulkan = gui_render->get_vulkan();
  this->vk_texture = vulkan->get_vk_texture();
  this->vk_image = nullptr;

  //---------------------------
}
GUI_stream::~GUI_stream(){}

//Main function
void GUI_stream::draw_stream(data::Image* image, ImVec2 panel_size){
  //---------------------------

  if(image->buffer != nullptr){
    this->convert_data_into_texture(image);
    ImGui::Image(texture, panel_size);
  }

  //---------------------------
}

//Subfunction
void GUI_stream::convert_data_into_texture(data::Image* image){
  //---------------------------

  if(vk_image == nullptr){
    vk_image = vk_texture->load_texture(image);
    VkDescriptorSet descriptor  = ImGui_ImplVulkan_AddTexture(vk_image->sampler, vk_image->view, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
    this->texture = reinterpret_cast<ImTextureID>(descriptor);
  }else{
    vk_image->data = image->buffer;
    vk_texture->update_texture(vk_image);
  }

  //---------------------------
}
