#include "Renderpass.h"

#include <Vulkan/Namespace.h>


namespace vk::renderpass{

//Constructor / Destructor
Renderpass::Renderpass(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_pipeline = new vk::pipeline::Pipeline(vk_struct);
  this->vk_subpass = new Subpass(vk_struct);
  this->vk_framebuffer = new vk::renderpass::Framebuffer(vk_struct);

  //---------------------------
}
Renderpass::~Renderpass(){}

//Main function
void Renderpass::init(){
  //---------------------------

  //Check for renderpass demande
  if(vk_struct->renderpass.vector.size() == 0){
    std::cout<<"[error] No renderpass initiated"<<std::endl;
    exit(0);
  }

  //Create renderpass according to the vec of renderpass demande
  for(auto& renderpass : vk_struct->renderpass.vector){
    this->init_renderpass(*renderpass);
  }

  //---------------------------
}
void Renderpass::clean(){
  //---------------------------

  for(auto& renderpass : vk_struct->renderpass.vector){
    this->clean_renderpass(*renderpass);
  }

  //---------------------------
}

//Subfunction
void Renderpass::init_renderpass(vk::structure::Renderpass& renderpass){
  //---------------------------

  vk_subpass->create_subpass(renderpass);
  this->subpass_description(renderpass);
  this->create_renderpass(renderpass);
  vk_pipeline->create_pipeline(renderpass);
  vk_framebuffer->create_framebuffer(renderpass);

  //---------------------------
}
void Renderpass::subpass_description(vk::structure::Renderpass& renderpass){
  //---------------------------

  //Get all related subpass descriptions, attachments and dependencies
  for(auto& subpass : renderpass.vec_subpass){
    // Add subpass description & dependency
    renderpass.vec_description.push_back(subpass->description);
    renderpass.vec_dependency.push_back(subpass->dependency);

    // Add color attachments
    for(int j=0; j<subpass->vec_color.size(); j++){
      renderpass.vec_attachment.push_back(subpass->vec_color[j].description);
    }

    // Add color resolve attachments
    for(int j=0; j<subpass->vec_color_resolve.size(); j++){
      renderpass.vec_attachment.push_back(subpass->vec_color_resolve[j].description);
    }

    // Add depth attachment
    renderpass.vec_attachment.push_back(subpass->depth.description);
  }

  //---------------------------
}
void Renderpass::create_renderpass(vk::structure::Renderpass& renderpass){
  //---------------------------

  //Create renderpass
  VkRenderPassCreateInfo renderpass_info{};
  renderpass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
  renderpass_info.attachmentCount = renderpass.vec_attachment.size();
  renderpass_info.pAttachments = renderpass.vec_attachment.data();
  renderpass_info.subpassCount = renderpass.vec_description.size();
  renderpass_info.pSubpasses = renderpass.vec_description.data();
  renderpass_info.dependencyCount = renderpass.vec_dependency.size();
  renderpass_info.pDependencies = renderpass.vec_dependency.data();

  //Render pass creation
  VkResult result = vkCreateRenderPass(vk_struct->device.handle, &renderpass_info, nullptr, &renderpass.handle);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create render pass!");
  }

  //---------------------------
}
void Renderpass::clean_renderpass(vk::structure::Renderpass& renderpass){
  //---------------------------

  vk_framebuffer->clean_framebuffer(renderpass);
  vkDestroyRenderPass(vk_struct->device.handle, renderpass.handle, nullptr);
  vk_pipeline->clean_pipeline(renderpass);

  //---------------------------
}

}
