#include "Subpass.h"

#include <Vulkan/Namespace.h>


namespace vk::renderpass{

//Constructor / Destructor
Subpass::Subpass(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_attachment = new Attachment(vk_struct);

  //---------------------------
}
Subpass::~Subpass(){}

//Main function
void Subpass::create_subpass(vk::structure::Renderpass& renderpass){
  //---------------------------

  for(auto& subpass : renderpass.vec_subpass){
    this->create_subpass_description(renderpass, *subpass);
  }

  //---------------------------
}

//Subfunction
void Subpass::create_subpass_description(vk::structure::Renderpass& renderpass, vk::structure::Subpass& subpass){
  //---------------------------

  //Subpass decription
  VkSubpassDescription subpass_description{};
  subpass_description.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
  subpass_description.pDepthStencilAttachment = &renderpass.attachment.depth.reference;
  subpass_description.colorAttachmentCount = renderpass.attachment.vec_color_ref.size();
  subpass_description.pColorAttachments = renderpass.attachment.vec_color_ref.data();
  if(!renderpass.attachment.vec_color_resolve_ref.empty())
  subpass_description.pResolveAttachments = renderpass.attachment.vec_color_resolve_ref.data();

  //Subpass dependencies
  VkSubpassDependency subpass_dependency{};
  subpass_dependency.srcSubpass = subpass.source; //Specified source and destination subpass
  subpass_dependency.dstSubpass = subpass.index; //Specified source and destination subpass
  subpass_dependency.srcAccessMask = 0;
  subpass_dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
  subpass_dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
  subpass_dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;

  //---------------------------
  renderpass.subpass.vec_description.push_back(subpass_description);
  renderpass.subpass.vec_dependency.push_back(subpass_dependency);
}

}
