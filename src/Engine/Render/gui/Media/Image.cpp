#include "Image.h"

#include <Engine/Node.h>
#include <Vulkan/Namespace.h>
#include <Utility/Function/File/Image.h>


namespace eng::render::gui{

//Constructor / Destructor
Image::Image(eng::Node* engine){
  //---------------------------

  vk::Vulkan* vulkan = engine->get_eng_vulkan();
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
    utl::media::Image struct_image = utl::fct::image::load_image(path);
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

  utl::media::Image struct_image = utl::fct::image::load_image(path);
  struct_image.format = "R8G8B8A8_SRGB";
  image = vk_texture->load_texture(&struct_image);
  VkDescriptorSet descriptor  = ImGui_ImplVulkan_AddTexture(image->sampler, image->view, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
  this->texture = reinterpret_cast<ImTextureID>(descriptor);

  //---------------------------
}
void Image::load_image_bin(string path){
  static vk::structure::Image* image;
  //---------------------------

  utl::media::Image struct_image = utl::fct::image::load_image(path);
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
