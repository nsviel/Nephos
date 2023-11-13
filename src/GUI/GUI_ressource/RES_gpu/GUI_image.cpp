#include "GUI_image.h"

#include <GUI.h>
#include <Vulkan.h>
#include <GUI_main/GUI_render/GUI_render.h>


//Constructor / Destructor
GUI_image::GUI_image(GUI* gui){
  //---------------------------

  GUI_render* gui_render = gui->get_gui_render();
  Vulkan* gui_vulkan = gui_render->get_gui_vulkan();
  this->vk_engine = gui_vulkan->get_vk_engine();

  //---------------------------
}
GUI_image::~GUI_image(){}

//Main function
void GUI_image::draw_image_static(string path){
  //---------------------------

  this->load_image_static(path);
  this->display_image();

  //---------------------------
}
void GUI_image::draw_image_dynamic(string path){
  //---------------------------

  this->load_image_dynamic(path);
  this->display_image();

  //---------------------------
}
void GUI_image::draw_image_bin(string path){
  //---------------------------

  this->load_image_bin(path);
  this->display_image();

  //---------------------------
}

//Subfunction
void GUI_image::load_image_static(string path){
  static Struct_image* image;
  //---------------------------

  if(image == nullptr){
    image = vk_engine->load_texture_from_file(path);
    VkDescriptorSet descriptor  = ImGui_ImplVulkan_AddTexture(image->sampler, image->view, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
    this->texture = reinterpret_cast<ImTextureID>(descriptor);
  }

  //---------------------------
}
void GUI_image::load_image_dynamic(string path){
  static Struct_image* image;
  //---------------------------

  image = vk_engine->load_texture_from_file(path);
  VkDescriptorSet descriptor  = ImGui_ImplVulkan_AddTexture(image->sampler, image->view, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
  this->texture = reinterpret_cast<ImTextureID>(descriptor);

  //---------------------------
}
void GUI_image::load_image_bin(string path){
  static Struct_image* image;
  //---------------------------

  image = vk_engine->load_texture_from_bin(path);
  VkDescriptorSet descriptor  = ImGui_ImplVulkan_AddTexture(image->sampler, image->view, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
  this->texture = reinterpret_cast<ImTextureID>(descriptor);

  //---------------------------
}
void GUI_image::display_image(){
  //---------------------------

  ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
  ImGui::Image(texture, ImVec2{viewportPanelSize.x, viewportPanelSize.y});

  //---------------------------
}
