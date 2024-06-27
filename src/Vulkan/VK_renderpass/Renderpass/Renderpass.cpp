#include "Renderpass.h"

#include <Vulkan/Namespace.h>


namespace vk::renderpass{

//Constructor / Destructor
Renderpass::Renderpass(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_pipeline = new vk::renderpass::Pipeline(vk_struct);
  this->vk_subpass = new Subpass(vk_struct);
  this->vk_framebuffer = new vk::renderpass::Framebuffer(vk_struct);

  //---------------------------
}
Renderpass::~Renderpass(){}

//Main function
void Renderpass::init(){
  //---------------------------

  //Check for renderpass demande
  if(vk_struct->render.vec_renderpass.size() == 0){
    std::cout<<"[error] No renderpass initiated"<<std::endl;
    exit(0);
  }

  //Create renderpass according to the vec of renderpass demande
  for(int i=0; i<vk_struct->render.vec_renderpass.size(); i++){
    vk::structure::Renderpass* renderpass = vk_struct->render.vec_renderpass[i];
    vk_subpass->create_subpass(renderpass);
    this->create_renderpass(renderpass);
    vk_pipeline->create_pipeline(renderpass);
    vk_framebuffer->create_framebuffer(renderpass);

  }

  //---------------------------
}
void Renderpass::clean(){
  //---------------------------

  for(int i=0; i<vk_struct->render.vec_renderpass.size(); i++){
    vk::structure::Renderpass* renderpass = vk_struct->render.vec_renderpass[i];
    this->clean_renderpass(renderpass);
  }

  //---------------------------
}

//Subfunction
void Renderpass::create_renderpass(vk::structure::Renderpass* renderpass){
  //---------------------------

  //Get all related subpass descriptions, attachments and dependencies
  std::vector<VkSubpassDescription> vec_description;
  std::vector<VkSubpassDependency> vec_dependency;
  std::vector<VkAttachmentDescription> vec_attachment;
  for(int i=0; i<renderpass->vec_subpass.size(); i++){
    vk::structure::Subpass* subpass = renderpass->vec_subpass[i];
    vec_description.push_back(subpass->description);
    vec_dependency.push_back(subpass->dependency);

    for(int j=0; j<subpass->vec_color.size(); j++){
      vec_attachment.push_back(subpass->vec_color[j].description);
    }
    for(int j=0; j<subpass->vec_color_resolve.size(); j++){
      vec_attachment.push_back(subpass->vec_color_resolve[j].description);
    }
    vec_attachment.push_back(subpass->depth.description);
  }

  //Create renderpass
  VkRenderPassCreateInfo renderpass_info{};
  renderpass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
  renderpass_info.attachmentCount = vec_attachment.size();
  renderpass_info.pAttachments = vec_attachment.data();
  renderpass_info.subpassCount = vec_description.size();
  renderpass_info.pSubpasses = vec_description.data();
  renderpass_info.dependencyCount = vec_dependency.size();
  renderpass_info.pDependencies = vec_dependency.data();

  //Render pass creation
  VkResult result = vkCreateRenderPass(vk_struct->device.handle, &renderpass_info, nullptr, &renderpass->handle);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create render pass!");
  }

  //---------------------------
}
void Renderpass::clean_renderpass(vk::structure::Renderpass* renderpass){
  //---------------------------

  vk_framebuffer->clean_framebuffer(renderpass);
  vkDestroyRenderPass(vk_struct->device.handle, renderpass->handle, nullptr);
  vk_pipeline->clean_pipeline(renderpass);

  //---------------------------
}

}
