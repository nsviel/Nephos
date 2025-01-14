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
  if(vk_struct->interface.param.headless) return;
  //---------------------------

  //Set presentation texture target
  vk::structure::Texture& render = vk_struct->graphics.render.presentation;
  render.surface = vk_struct->graphics.render.renderpass.postprocess->framebuffer.color;

  //Create presentation texture descriptor
  this->create_image_descriptor(render);

  //Set presentation texture target
  vk::structure::Texture& depth = vk_struct->graphics.render.depth;
  depth.surface = vk_struct->graphics.render.renderpass.geometry->framebuffer.depth;

  //Create presentation texture descriptor
  this->create_image_descriptor(depth);

  //---------------------------
}
void Render::create_image_descriptor(vk::structure::Texture& texture){
  //---------------------------

  texture.descriptor_set = ImGui_ImplVulkan_AddTexture(texture.surface.sampler, texture.surface.view, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

  //---------------------------
}
void Render::display_image(vk::structure::Texture& texture, glm::vec2 dimension){
  //---------------------------

  //Check if descriptor set is initialized
  if(texture.descriptor_set == VK_NULL_HANDLE){
    this->create_image_descriptor(texture);
  }

  //Convert descriptor set into imgui texture ID
  ImTextureID imtexture = reinterpret_cast<ImTextureID>(texture.descriptor_set);
  if(imtexture == 0) return;

  //Display image dimension
  ImGui::Image(imtexture, ImVec2(dimension.x, dimension.y));

  //---------------------------
}

}
