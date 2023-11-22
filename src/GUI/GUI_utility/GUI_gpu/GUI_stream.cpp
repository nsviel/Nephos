#include "GUI_stream.h"

#include <GUI.h>
#include <Vulkan.h>
#include <VK_main/VK_texture.h>
#include <GUI_main/GUI_render/GUI_render.h>
#include <UTL_struct/Struct_image.h>


//Constructor / Destructor
GUI_stream::GUI_stream(GUI* gui){
  //---------------------------

  GUI_render* gui_render = gui->get_gui_render();
  Vulkan* vulkan = gui_render->get_vulkan();
  this->vk_texture = vulkan->get_vk_texture();

  //---------------------------
}
GUI_stream::~GUI_stream(){}

//Main function
void GUI_stream::draw_stream(Struct_image* struct_image){
  //---------------------------

  if(struct_image->buffer != nullptr){
    this->convert_data_into_texture(struct_image);
    this->display_frame();
  }

  //---------------------------
}

//Subfunction
void GUI_stream::convert_data_into_texture(Struct_image* struct_image){
  //---------------------------

  static Struct_vk_image* image = nullptr;

  if(image == nullptr){
    image = vk_texture->load_texture(struct_image);
    VkDescriptorSet descriptor  = ImGui_ImplVulkan_AddTexture(image->sampler, image->view, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
    this->texture = reinterpret_cast<ImTextureID>(descriptor);
  }else{
    image->data = struct_image->buffer;
    vk_texture->update_texture(image);
  }

  //---------------------------
}
void GUI_stream::display_frame(){
  //---------------------------

  ImVec2 panel_size = ImGui::GetContentRegionAvail();
  ImGui::Image(texture, ImVec2{panel_size.x, panel_size.y/3});

  //---------------------------
}
