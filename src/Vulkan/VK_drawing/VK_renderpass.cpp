#include "VK_renderpass.h"

#include <VK_pipeline/VK_subpass.h>
#include <VK_main/VK_engine.h>
#include <VK_struct/struct_vulkan.h>
#include <VK_command/VK_command_buffer.h>
#include <VK_pipeline/VK_pipeline.h>
#include <VK_presentation/VK_frame.h>
#include <VK_presentation/VK_framebuffer.h>
#include <VK_image/VK_color.h>
#include <VK_image/VK_depth.h>

#include <ENG_vulkan/ENG_scene.h>
#include <ENG_vulkan/ENG_edl.h>
#include <ENG_vulkan/ENG_gui.h>


//Constructor / Destructor
VK_renderpass::VK_renderpass(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->struct_vulkan = vk_engine->get_struct_vulkan();
  this->vk_color = new VK_color(vk_engine);
  this->vk_pipeline = new VK_pipeline(vk_engine);
  this->vk_subpass = new VK_subpass(vk_engine);
  this->vk_command_buffer = new VK_command_buffer(vk_engine);

  this->eng_scene = new ENG_scene(vk_engine);
  this->eng_edl = new ENG_edl(vk_engine);
  this->eng_gui = new ENG_gui(vk_engine);

  //---------------------------
}
VK_renderpass::~VK_renderpass(){}

//Main function
void VK_renderpass::init_renderpass(){
  //---------------------------

  Struct_renderpass* renderpass;

  renderpass = eng_scene->init_renderpass();
  struct_vulkan->vec_renderpass.push_back(renderpass);

  renderpass = eng_edl->init_renderpass();
  struct_vulkan->vec_renderpass.push_back(renderpass);

  renderpass = eng_gui->init_renderpass();
  struct_vulkan->vec_renderpass.push_back(renderpass);

  //---------------------------
}
void VK_renderpass::clean_renderpass(){
  //---------------------------

  for(int i=0; i<struct_vulkan->vec_renderpass.size(); i++){
    Struct_renderpass* renderpass = struct_vulkan->vec_renderpass[i];
    this->clean_renderpass_object(renderpass);
  }

  //---------------------------
}

//Subfunction
void VK_renderpass::clean_renderpass_object(Struct_renderpass* renderpass){
  VK_frame* vk_frame = vk_engine->get_vk_frame();
  //---------------------------

  vk_frame->clean_frame_renderpass(renderpass);
  vkDestroyRenderPass(struct_vulkan->device.device, renderpass->renderpass, nullptr);
  vk_pipeline->clean_pipeline(renderpass);

  //---------------------------
}
void VK_renderpass::create_renderpass(Struct_renderpass* renderpass){
  VK_frame* vk_frame = vk_engine->get_vk_frame();
  //---------------------------

  this->create_renderpass_obj(renderpass);
  vk_command_buffer->allocate_command_buffer_primary(renderpass);
  vk_pipeline->create_pipeline(renderpass);
  vk_frame->create_frame_renderpass(renderpass);

  //---------------------------
}
void VK_renderpass::create_renderpass_obj(Struct_renderpass* renderpass){
  //---------------------------

  renderpass->color_image_usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
  renderpass->color_sampler_layout = IMAGE_LAYOUT_SHADER_READONLY;
  renderpass->depth_image_usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
  renderpass->depth_sampler_layout = IMAGE_LAYOUT_DEPTH_READONLY;

  Struct_subpass* subpass_ref = renderpass->vec_subpass[0];

  vector<VkSubpassDescription> vec_description;
  vector<VkSubpassDependency> vec_dependency;
  for(int i=0; i<renderpass->vec_subpass.size(); i++){
    Struct_subpass* subpass = renderpass->vec_subpass[i];
    vec_description.push_back(subpass->description);
    vec_dependency.push_back(subpass->dependency);
  }

  VkRenderPassCreateInfo renderpass_info{};
  renderpass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
  renderpass_info.attachmentCount = static_cast<uint32_t>(subpass_ref->vec_attachment_description.size());
  renderpass_info.pAttachments = subpass_ref->vec_attachment_description.data();
  renderpass_info.subpassCount = vec_description.size();
  renderpass_info.pSubpasses = vec_description.data();
  renderpass_info.dependencyCount = vec_dependency.size();
  renderpass_info.pDependencies = vec_dependency.data();

  //Render pass creation
  VkResult result = vkCreateRenderPass(struct_vulkan->device.device, &renderpass_info, nullptr, &renderpass->renderpass);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create render pass!");
  }

  //---------------------------
}
