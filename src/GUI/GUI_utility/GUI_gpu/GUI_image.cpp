#include "GUI_image.h"

#include <GUI.h>
#include <Vulkan.h>
#include <GUI_main/GUI_render/GUI_render.h>
#include <UTL_file/Image.h>
#include <UTL_struct/Struct_image.h>
#include <VK_main/VK_texture.h>


//Constructor / Destructor
GUI_image::GUI_image(GUI* gui){
  //---------------------------

  GUI_render* gui_render = gui->get_gui_render();
  Vulkan* gui_vulkan = gui_render->get_gui_vulkan();
  this->vk_texture = gui_vulkan->get_vk_texture();

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
  static Struct_vk_image* image = nullptr;
  //---------------------------

  if(image == nullptr){
    Struct_image struct_image = image::load_image(path);
    struct_image.format = "R8G8B8A8_SRGB";
    image = vk_texture->load_texture(&struct_image);
    VkDescriptorSet descriptor  = ImGui_ImplVulkan_AddTexture(image->sampler, image->view, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
    this->texture = reinterpret_cast<ImTextureID>(descriptor);
  }

  //---------------------------
}
void GUI_image::load_image_dynamic(string path){
  static Struct_vk_image* image;
  //---------------------------

  Struct_image struct_image = image::load_image(path);
  struct_image.format = "R8G8B8A8_SRGB";
  image = vk_texture->load_texture(&struct_image);
  VkDescriptorSet descriptor  = ImGui_ImplVulkan_AddTexture(image->sampler, image->view, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
  this->texture = reinterpret_cast<ImTextureID>(descriptor);

  //---------------------------
}
void GUI_image::load_image_bin(string path){
  static Struct_vk_image* image;
  //---------------------------

  Struct_image struct_image = image::load_image(path);
  struct_image.format = "R8G8B8A8_SRGB";
  image = vk_texture->load_texture(&struct_image);
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
