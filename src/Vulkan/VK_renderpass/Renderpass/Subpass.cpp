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
    switch(subpass->target){
      case vk::renderpass::SHADER:{
        this->create_subpass_shader(*subpass);
        break;
      }
      case vk::renderpass::TRANSFER:{
        this->create_subpass_transfert(*subpass);
        break;
      }
      case vk::renderpass::PRESENTATION:{
        this->create_subpass_presentation(*subpass);
        break;
      }
      default:{
        std::cout<<"[error] subpass target not recognized"<<std::endl;
        return;
      }
    }

    this->create_subpass_description(*subpass);
  }

  //---------------------------
}

//Subfunction
void Subpass::create_subpass_shader(vk::structure::Subpass& subpass){
  //---------------------------

  // Color
  vk::structure::Attachment color;
  color.index = vk::renderpass::ID_COLOR;
  color.layout_final = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
  vk_attachment->color_description(color);
  vk_attachment->color_reference(color);
  subpass.vec_color.push_back(color);

  // Depth
  vk::structure::Attachment depth;
  depth.index = vk::renderpass::ID_DEPTH;
  depth.layout_final = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;
  vk_attachment->depth_description(depth);
  vk_attachment->depth_reference(depth);
  subpass.depth = depth;

  // Color resolver
  vk::structure::Attachment color_resolve;
  color_resolve.index = vk::renderpass::ID_COLOR;
  color_resolve.layout_final = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
  vk_attachment->color_resolve_description(color_resolve);
  vk_attachment->color_resolve_reference(color_resolve);
  //subpass.vec_color_resolve.push_back(color_resolve);

  //---------------------------
}
void Subpass::create_subpass_transfert(vk::structure::Subpass& subpass){
  //---------------------------

  // Color
  vk::structure::Attachment color;
  color.index = vk::renderpass::ID_COLOR;
  color.layout_final = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
  vk_attachment->color_description(color);
  vk_attachment->color_reference(color);
  subpass.vec_color.push_back(color);

  // Depth
  vk::structure::Attachment depth;
  depth.index = vk::renderpass::ID_DEPTH;
  depth.layout_final = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;
  vk_attachment->depth_description(depth);
  vk_attachment->depth_reference(depth);
  subpass.depth = depth;

  //---------------------------
}
void Subpass::create_subpass_presentation(vk::structure::Subpass& subpass){
  //---------------------------

  // Color
  vk::structure::Attachment color;
  color.index = vk::renderpass::ID_COLOR;
  color.layout_final = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
  vk_attachment->color_description(color);
  vk_attachment->color_reference(color);
  subpass.vec_color.push_back(color);

  // Depth
  vk::structure::Attachment depth;
  depth.index = vk::renderpass::ID_DEPTH;
  depth.layout_final = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;
  vk_attachment->depth_description(depth);
  vk_attachment->depth_reference(depth);
  subpass.depth = depth;

  //---------------------------
}
void Subpass::create_subpass_description(vk::structure::Subpass& subpass){
  //---------------------------

  //Format elements
  uint32_t nb_color_attachment = 0;
  std::vector<VkAttachmentReference*> vec_color;
  for(int i=0; i<subpass.vec_color.size(); i++){
    vec_color.push_back(&subpass.vec_color[0].reference);
  }
  nb_color_attachment += subpass.vec_color.size();
  std::vector<VkAttachmentReference*> vec_color_resolve;
  for(int i=0; i<subpass.vec_color_resolve.size(); i++){
    vec_color_resolve.push_back(&subpass.vec_color_resolve[0].reference);
  }
  nb_color_attachment += subpass.vec_color_resolve.size();

  //Subpass decription
  VkSubpassDescription subpass_description{};
  subpass_description.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
  subpass_description.pDepthStencilAttachment = &subpass.depth.reference;
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
