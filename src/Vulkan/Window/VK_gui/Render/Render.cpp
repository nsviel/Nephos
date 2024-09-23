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

  //Render image
  vk::structure::Image& image = vk_struct->render.renderpass.postprocess.framebuffer.color;

  //Create gui image descriptor
  this->create_image_descriptor(image, vk_struct->window.gui.descriptor_set);

  //---------------------------
}
void Render::create_image_descriptor(vk::structure::Image& image, VkDescriptorSet& descriptor_set){
  //---------------------------

  descriptor_set = ImGui_ImplVulkan_AddTexture(image.sampler, image.view, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

  //---------------------------
}
ImTextureID Render::query_render_texture(){
  //---------------------------

  ImTextureID texture = reinterpret_cast<ImTextureID>(vk_struct->window.gui.descriptor_set);

  //---------------------------
  return texture;
}

}
