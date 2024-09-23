#include "Render.h"

#include <Utility/Namespace.h>
#include <Vulkan/Namespace.h>
#include <imgui/core/imgui.h>
#include <imgui/core/imgui_impl_glfw.h>
#include <imgui/vulkan/imgui_impl_vulkan.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace vk::gui{

//Constructor / Destructor
Render::Render(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;

  //---------------------------
}
Render::~Render(){}

//Main function
void Render::update_render_texture(){
  if(vk_struct->param.headless) return;
  //---------------------------

  //Set presentation texture target
  vk::structure::Texture& texture = vk_struct->render.presentation.texture;
  texture.wrapper = vk_struct->render.renderpass.postprocess.framebuffer.color;

  //Create presentation texture descriptor
  this->create_image_descriptor(texture);

  //---------------------------
}
void Render::create_image_descriptor(vk::structure::Texture& texture){
  //---------------------------

  texture.descriptor_set = ImGui_ImplVulkan_AddTexture(texture.wrapper.sampler, texture.wrapper.view, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

  //---------------------------
}
void Render::render_image_in_gui(vk::structure::Texture& texture, ImVec2 dimension){
  //---------------------------

  if(texture.descriptor_set = VK_NULL_HANDLE){
    this->create_image_descriptor(texture);
  }

  ImGui::Image(texture.descriptor_set, dimension);

  //---------------------------
}
ImTextureID Render::query_render_texture(){
  //---------------------------

  ImTextureID texture = reinterpret_cast<ImTextureID>(vk_struct->render.presentation.texture.descriptor_set);

  //---------------------------
  return texture;
}

}
