#include "VK_renderpass.h"

#include <VK_renderpass/VK_subpass.h>
#include <VK_main/VK_engine.h>
#include <VK_struct/Struct_vulkan.h>
#include <VK_command/VK_command_buffer.h>
#include <VK_pipeline/VK_pipeline.h>
#include <VK_presentation/VK_frame.h>
#include <VK_presentation/VK_framebuffer.h>
#include <VK_image/VK_color.h>
#include <VK_image/VK_depth.h>


//Constructor / Destructor
VK_renderpass::VK_renderpass(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->struct_vulkan = vk_engine->get_struct_vulkan();
  this->vk_color = new VK_color(vk_engine);
  this->vk_pipeline = new VK_pipeline(vk_engine);
  this->vk_subpass = new VK_subpass(vk_engine);
  this->vk_command_buffer = new VK_command_buffer(vk_engine);
  this->vk_frame = new VK_frame(vk_engine);
  this->vk_framebuffer = new VK_framebuffer(vk_engine);

  //---------------------------
}
VK_renderpass::~VK_renderpass(){}

//Main function
void VK_renderpass::init_renderpass(){
  //---------------------------

  if(struct_vulkan->vec_renderpass.size() == 0){
    cout<<"[error] No renderpass initiated"<<endl;
    exit(0);
  }

  for(int i=0; i<struct_vulkan->vec_renderpass.size(); i++){
    Struct_renderpass* renderpass = struct_vulkan->vec_renderpass[i];
    vk_subpass->create_subpass(renderpass);
    this->create_renderpass(renderpass);
  }

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
  //---------------------------

  vk_framebuffer->clean_framebuffer(renderpass);
  vkDestroyRenderPass(struct_vulkan->device.device, renderpass->renderpass, nullptr);
  vk_pipeline->clean_pipelines(renderpass);

  //---------------------------
}
void VK_renderpass::create_renderpass(Struct_renderpass* renderpass){
  //---------------------------

  this->create_renderpass_obj(renderpass);
  vk_command_buffer->allocate_command_buffer_primary(renderpass);
  vk_pipeline->create_pipelines(renderpass);
  vk_framebuffer->create_framebuffer(renderpass);

  //---------------------------
}
void VK_renderpass::create_renderpass_obj(Struct_renderpass* renderpass){
  //---------------------------

  //Get all related subpass descriptions, attachments and dependencies
  vector<VkSubpassDescription> vec_description;
  vector<VkSubpassDependency> vec_dependency;
  vector<VkAttachmentDescription> vec_attachment;
  for(int i=0; i<renderpass->vec_subpass.size(); i++){
    Struct_subpass* subpass = renderpass->vec_subpass[i];
    vec_description.push_back(subpass->description);
    vec_dependency.push_back(subpass->dependency);

    for(int j=0; j<subpass->vec_color.size(); j++){
      vec_attachment.push_back(subpass->vec_color[j].description);
    }
    vec_attachment.push_back(subpass->depth.description);
  }

  //Create renderpass
  VkRenderPassCreateInfo renderpass_info{};
  renderpass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
  renderpass_info.attachmentCount = static_cast<uint32_t>(vec_attachment.size());
  renderpass_info.pAttachments = vec_attachment.data();
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
