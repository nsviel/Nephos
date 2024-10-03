#include "Renderpass.h"

#include <Vulkan/Namespace.h>


namespace vk::renderpass{

//Constructor / Destructor
Renderpass::Renderpass(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_pipeline = new vk::render::Pipeline(vk_struct);
  this->vk_subpass = new Subpass(vk_struct);
  this->vk_framebuffer = new vk::renderpass::Framebuffer(vk_struct);
  this->vk_attachment = new Attachment(vk_struct);

  //---------------------------
}
Renderpass::~Renderpass(){}

//Main function
void Renderpass::init(){
  //---------------------------

  //Check for renderpass demande
  if(vk_struct->graphics.render.renderpass.vec_renderpass.size() == 0){
    std::cout<<"[error] No renderpass initiated"<<std::endl;
    exit(0);
  }

  //Create renderpass according to the vec of renderpass demande
  for(auto& renderpass : vk_struct->graphics.render.renderpass.vec_renderpass){
    this->init_renderpass(*renderpass);
  }

  this->actualize_sampler();

  //---------------------------
}
void Renderpass::clean(){
  //---------------------------

  for(auto& renderpass : vk_struct->graphics.render.renderpass.vec_renderpass){
    this->clean_renderpass(*renderpass);
  }

  //---------------------------
}

//Subfunction
void Renderpass::init_renderpass(vk::structure::Renderpass& renderpass){
  //---------------------------

  this->attachment_renderpass(renderpass);
  vk_subpass->create_subpass(renderpass);
  this->create_renderpass(renderpass);
  vk_pipeline->create_pipeline(renderpass);
  vk_framebuffer->create_framebuffer(renderpass);

  //---------------------------
}
void Renderpass::attachment_renderpass(vk::structure::Renderpass& renderpass){
  //---------------------------

  switch(renderpass.attachment.target){
    case vk::renderpass::SHADER:{
      vk_attachment->attachment_shader(renderpass);
      break;
    }
    case vk::renderpass::TRANSFER:{
      vk_attachment->attachment_transfert(renderpass);
      break;
    }
    case vk::renderpass::PRESENTATION:{
      vk_attachment->attachment_presentation(renderpass);
      break;
    }
    default:{
      std::cout<<"[error] renderpass attachment target not recognized"<<std::endl;
      return;
    }
  }

  //---------------------------
}
void Renderpass::create_renderpass(vk::structure::Renderpass& renderpass){
  //---------------------------

  //Create renderpass
  VkRenderPassCreateInfo renderpass_info{};
  renderpass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
  renderpass_info.attachmentCount = renderpass.attachment.vec_description.size();
  renderpass_info.pAttachments = renderpass.attachment.vec_description.data();
  renderpass_info.subpassCount = renderpass.subpass.vec_description.size();
  renderpass_info.pSubpasses = renderpass.subpass.vec_description.data();
  renderpass_info.dependencyCount = renderpass.subpass.vec_dependency.size();
  renderpass_info.pDependencies = renderpass.subpass.vec_dependency.data();

  //Render pass creation
  VkResult result = vkCreateRenderPass(vk_struct->core.device.handle, &renderpass_info, nullptr, &renderpass.handle);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create render pass!");
  }

  //---------------------------
}
void Renderpass::clean_renderpass(vk::structure::Renderpass& renderpass){
  //---------------------------

  vk_framebuffer->clean_framebuffer(renderpass);
  vk_pipeline->clean_pipeline(renderpass);
  vkDestroyRenderPass(vk_struct->core.device.handle, renderpass.handle, nullptr);

  //---------------------------
}
void Renderpass::actualize_sampler(){
  //---------------------------

  for(auto& renderpass : vk_struct->graphics.render.renderpass.vec_renderpass){
    for(auto& subpass : renderpass->vec_subpass){
      subpass->update_sampler(*subpass);
    }
  }

  //---------------------------
}

}
