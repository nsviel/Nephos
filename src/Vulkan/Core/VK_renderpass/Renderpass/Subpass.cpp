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

  //Format elements
  uint32_t nb_color_attachment = 0;
  std::vector<VkAttachmentReference*> vec_color;
  for(int i=0; i<renderpass.vec_color.size(); i++){
    vec_color.push_back(&renderpass.vec_color[0].reference);
  }
  nb_color_attachment += renderpass.vec_color.size();
  std::vector<VkAttachmentReference*> vec_color_resolve;
  for(int i=0; i<renderpass.vec_color_resolve.size(); i++){
    vec_color_resolve.push_back(&renderpass.vec_color_resolve[0].reference);
  }
  nb_color_attachment += renderpass.vec_color_resolve.size();

  //Subpass decription
  VkSubpassDescription subpass_description{};
  subpass_description.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
  subpass_description.pDepthStencilAttachment = &renderpass.depth.reference;
  subpass_description.colorAttachmentCount = nb_color_attachment;
  subpass_description.pColorAttachments = *vec_color.data();
  if(vec_color_resolve.size() != 0)
  subpass_description.pResolveAttachments = *vec_color_resolve.data();

  //Subpass dependencies
  VkSubpassDependency subpass_dependency{};
  subpass_dependency.srcSubpass = subpass.source; //Specified source and destination subpass
  subpass_dependency.dstSubpass = subpass.index; //Specified source and destination subpass
  subpass_dependency.srcAccessMask = 0;
  subpass_dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
  subpass_dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
  subpass_dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;

  //---------------------------
  subpass.description = subpass_description;
  subpass.dependency = subpass_dependency;
}

}
