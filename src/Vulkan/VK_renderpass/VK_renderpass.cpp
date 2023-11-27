#include "VK_renderpass.h"

#include <VK_renderpass/VK_subpass.h>
#include <VK_main/Struct_vulkan.h>
#include <VK_pipeline/VK_pipeline.h>
#include <VK_render/VK_framebuffer.h>
#include <VK_command/VK_command.h>


//Constructor / Destructor
VK_renderpass::VK_renderpass(Struct_vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_pipeline = new VK_pipeline(struct_vulkan);
  this->vk_subpass = new VK_subpass(struct_vulkan);
  this->vk_framebuffer = new VK_framebuffer(struct_vulkan);
  this->vk_command = new VK_command(struct_vulkan);

  //---------------------------
}
VK_renderpass::~VK_renderpass(){}

//Main function
void VK_renderpass::init_renderpass(){
  //---------------------------

  if(struct_vulkan->render.vec_renderpass.size() == 0){
    cout<<"[error] No renderpass initiated"<<endl;
    exit(0);
  }

  for(int i=0; i<struct_vulkan->render.vec_renderpass.size(); i++){
    Struct_vk_renderpass* renderpass = struct_vulkan->render.vec_renderpass[i];
    vk_subpass->create_subpass(renderpass);
    this->create_renderpass_struct(renderpass);
  }

  //---------------------------
}
void VK_renderpass::clean_renderpass(){
  //---------------------------

  for(int i=0; i<struct_vulkan->render.vec_renderpass.size(); i++){
    Struct_vk_renderpass* renderpass = struct_vulkan->render.vec_renderpass[i];
    this->clean_renderpass_struct(renderpass);
  }

  //---------------------------
}

//Subfunction
void VK_renderpass::create_renderpass_struct(Struct_vk_renderpass* renderpass){
  //---------------------------

  this->create_renderpass_obj(renderpass);
  vk_pipeline->create_pipeline(renderpass);
  vk_framebuffer->create_framebuffer(renderpass);
  vk_command->allocate_command_buffer_primary(renderpass->command_buffer);

  //---------------------------
}
void VK_renderpass::create_renderpass_obj(Struct_vk_renderpass* renderpass){
  //---------------------------

  //Get all related subpass descriptions, attachments and dependencies
  vector<VkSubpassDescription> vec_description;
  vector<VkSubpassDependency> vec_dependency;
  vector<VkAttachmentDescription> vec_attachment;
  for(int i=0; i<renderpass->vec_subpass.size(); i++){
    Struct_vk_subpass* subpass = renderpass->vec_subpass[i];
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
void VK_renderpass::clean_renderpass_struct(Struct_vk_renderpass* renderpass){
  //---------------------------

  vk_framebuffer->clean_framebuffer(renderpass);
  vkDestroyRenderPass(struct_vulkan->device.device, renderpass->renderpass, nullptr);
  vk_pipeline->clean_pipeline(renderpass);

  //---------------------------
}
