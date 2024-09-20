#include "Texture.h"

#include <Utility/Namespace.h>
#include <Vulkan/Namespace.h>
#include <imgui/core/imgui.h>
#include <imgui/core/imgui_impl_glfw.h>
#include <imgui/vulkan/imgui_impl_vulkan.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace vk::gui{

//Constructor / Destructor
Texture::Texture(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_texture = new vk::texture::Ressource(vk_struct);

  //---------------------------
}
Texture::~Texture(){}

//Main function
void Texture::insert_texture(std::shared_ptr<utl::media::Image> utl_image){
  //---------------------------

  utl_image->gui_texture_ID = create_imgui_texture(utl_image->texture_ID);

  //---------------------------
}
void Texture::update_render_texture(){
  if(vk_struct->param.headless) return;
  //---------------------------

  vk::structure::Renderpass& renderpass = vk_struct->render.renderpass.postprocess;
  vk::structure::Image* image = &renderpass.framebuffer.color;

  vk_struct->window.gui.descriptor = ImGui_ImplVulkan_AddTexture(image->sampler, image->view, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

  //---------------------------
}
ImTextureID Texture::create_imgui_texture(int UID){
  //---------------------------

  std::shared_ptr<vk::structure::Texture> texture = vk_texture->query_texture(UID);
  if(!texture) return 0;

  //Retrieve descriptor from vulkan texture
  VkDescriptorSet descriptor  = ImGui_ImplVulkan_AddTexture(texture->wrapper.sampler, texture->wrapper.view, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
  ImTextureID imgui_texture = reinterpret_cast<ImTextureID>(descriptor);

  //---------------------------
  return imgui_texture;
}
ImTextureID Texture::query_render_texture(){
  if(vk_struct->window.gui.descriptor == VK_NULL_HANDLE) return 0;
  //---------------------------

  ImTextureID texture = reinterpret_cast<ImTextureID>(vk_struct->window.gui.descriptor);

  //---------------------------
  return texture;
}

}
