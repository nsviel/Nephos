#include "GUI_stream.h"

#include <GUI.h>
#include <Vulkan.h>
#include <VK_main/VK_engine.h>
#include <GUI_main/GUI_render/GUI_render.h>


//Constructor / Destructor
GUI_stream::GUI_stream(GUI* gui){
  //---------------------------

  GUI_render* gui_render = gui->get_gui_render();
  Vulkan* gui_vulkan = gui_render->get_gui_vulkan();
  this->vk_engine = gui_vulkan->get_vk_engine();

  //---------------------------
}
GUI_stream::~GUI_stream(){}

//Main function
void GUI_stream::draw_video(uint8_t* data, int width, int height){
  //---------------------------

  if(data != nullptr){
    this->convert_data_into_texture(data, width, height);
    this->display_frame();
  }

  //---------------------------
}

//Subfunction
void GUI_stream::convert_data_into_texture(uint8_t* data, int width, int height){
  //---------------------------

  static Struct_vk_image* image = nullptr;

  if(image == nullptr){
    image = vk_engine->load_texture_from_data(data, width, height);
    VkDescriptorSet descriptor  = ImGui_ImplVulkan_AddTexture(image->sampler, image->view, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
    this->texture = reinterpret_cast<ImTextureID>(descriptor);
  }else{
    vk_engine->update_texture_from_data(image, data);
  }

  //---------------------------
}
void GUI_stream::display_frame(){
  //---------------------------

  ImVec2 panel_size = ImGui::GetContentRegionAvail();
  ImGui::Image(texture, ImVec2{panel_size.x, panel_size.y/3});

  //---------------------------
}
