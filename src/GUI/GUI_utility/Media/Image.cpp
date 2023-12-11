#include "Image.h"

#include <Node/GUI.h>
#include <Vulkan/Vulkan.h>
#include <GUI/GUI_main/Render/Render.h>
#include <Utility/Function/File/Image.h>
#include <Utility/Base/Struct_image.h>
#include <Vulkan/VK_main/VK_texture.h>


namespace gui::media{

//Constructor / Destructor
Image::Image(GUI* gui){
  //---------------------------

  Render* gui_render = gui->get_rnd_tab();
  Vulkan* vulkan = gui_render->get_vulkan();
  this->vk_texture = vulkan->get_vk_texture();

  //---------------------------
}
Image::~Image(){}

//Main function
void Image::draw_image_static(string path){
  //---------------------------

  this->load_image_static(path);
  this->display_image();

  //---------------------------
}
void Image::draw_image_dynamic(string path){
  //---------------------------

  this->load_image_dynamic(path);
  this->display_image();

  //---------------------------
}
void Image::draw_image_bin(string path){
  //---------------------------

  this->load_image_bin(path);
  this->display_image();

  //---------------------------
}

//Subfunction
void Image::load_image_static(string path){
  static vk::structure::Image* image = nullptr;
  //---------------------------

  if(image == nullptr){
    utility::base::Image struct_image = image::load_image(path);
    struct_image.format = "R8G8B8A8_SRGB";
    image = vk_texture->load_texture(&struct_image);
    VkDescriptorSet descriptor  = ImGui_ImplVulkan_AddTexture(image->sampler, image->view, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
    this->texture = reinterpret_cast<ImTextureID>(descriptor);
  }

  //---------------------------
}
void Image::load_image_dynamic(string path){
  static vk::structure::Image* image;
  //---------------------------

  utility::base::Image struct_image = image::load_image(path);
  struct_image.format = "R8G8B8A8_SRGB";
  image = vk_texture->load_texture(&struct_image);
  VkDescriptorSet descriptor  = ImGui_ImplVulkan_AddTexture(image->sampler, image->view, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
  this->texture = reinterpret_cast<ImTextureID>(descriptor);

  //---------------------------
}
void Image::load_image_bin(string path){
  static vk::structure::Image* image;
  //---------------------------

  utility::base::Image struct_image = image::load_image(path);
  struct_image.format = "R8G8B8A8_SRGB";
  image = vk_texture->load_texture(&struct_image);
  VkDescriptorSet descriptor  = ImGui_ImplVulkan_AddTexture(image->sampler, image->view, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
  this->texture = reinterpret_cast<ImTextureID>(descriptor);

  //---------------------------
}
void Image::display_image(){
  //---------------------------

  ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
  ImGui::Image(texture, ImVec2{viewportPanelSize.x, viewportPanelSize.y});

  //---------------------------
}

}
