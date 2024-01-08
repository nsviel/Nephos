#include "VK_subpass.h"

#include <Vulkan/VK_struct/Namespace.h>
#include <Vulkan/VK_command/VK_command.h>
#include <Vulkan/VK_renderpass/VK_attachment.h>

/*
  Attachment index is defined as follow:
    - 0 color
    - 1 depth
    - 2 texture

    - 0 color
    - 1 color
    - 2 color resolve
    - 3 depth
    - 4 texture
*/

//Constructor / Destructor
VK_subpass::VK_subpass(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_command = new VK_command(struct_vulkan);
  this->vk_attachment = new VK_attachment(struct_vulkan);

  //---------------------------
}
VK_subpass::~VK_subpass(){}

//Main function
void VK_subpass::create_subpass(vk::structure::Renderpass* renderpass){
  //---------------------------

  for(int i=0; i<renderpass->vec_subpass.size(); i++){
    vk::structure::Subpass* subpass = renderpass->vec_subpass[i];

    if(subpass->target == "shader"){
      this->create_subpass_shader(subpass);
      this->create_subpass_description(subpass);
    }
    else if(subpass->target == "transfert"){
      this->create_subpass_transfert(subpass);
      this->create_subpass_description(subpass);
    }
    else if(subpass->target == "presentation"){
      this->create_subpass_presentation(subpass);
      this->create_subpass_description(subpass);
    }
    else{
      cout<<"[error] subpass target not recognized"<<endl;
    }
  }

  //---------------------------
}

//Subpass type
void VK_subpass::create_subpass_shader(vk::structure::Subpass* subpass){
  //---------------------------

  // Color
  vk::structure::Attachment color;
  color.index = 0;
  color.store_operation = TYP_ATTACHMENT_STOREOP_STORE;
  color.layout_initial = TYP_IMAGE_LAYOUT_EMPTY;
  color.layout_final = TYP_IMAGE_LAYOUT_SHADER_READONLY;
  vk_attachment->color_description(color);
  vk_attachment->color_reference(color);
  subpass->vec_color.push_back(color);

  // Depth
  vk::structure::Attachment depth;
  depth.index = 1;
  depth.store_operation = TYP_ATTACHMENT_STOREOP_STORE;
  depth.layout_initial = TYP_IMAGE_LAYOUT_EMPTY;
  depth.layout_final = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;
  vk_attachment->depth_description(depth);
  vk_attachment->depth_reference(depth);
  subpass->depth = depth;

  //Color resolver
  vk::structure::Attachment color_resolve;
  color_resolve.index = 1;
  vk_attachment->color_resolve_description(color_resolve);
  vk_attachment->color_resolve_reference(color_resolve);
  //subpass->vec_color_resolve.push_back(color_resolve);

  //---------------------------
}
void VK_subpass::create_subpass_transfert(vk::structure::Subpass* subpass){
  //---------------------------

  // Depth
  vk::structure::Attachment depth;
  depth.index = 1;
  depth.store_operation = TYP_ATTACHMENT_STOREOP_STORE;
  depth.layout_initial = TYP_IMAGE_LAYOUT_EMPTY;
  depth.layout_final = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;
  vk_attachment->depth_description(depth);
  vk_attachment->depth_reference(depth);
  subpass->depth = depth;

  // Color
  vk::structure::Attachment color;
  color.index = 0;
  color.store_operation = TYP_ATTACHMENT_STOREOP_STORE;
  color.layout_initial = TYP_IMAGE_LAYOUT_EMPTY;
  color.layout_final = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
  vk_attachment->color_description(color);
  vk_attachment->color_reference(color);
  subpass->vec_color.push_back(color);

  //---------------------------
}
void VK_subpass::create_subpass_presentation(vk::structure::Subpass* subpass){
  //---------------------------

  // Color
  vk::structure::Attachment color;
  color.index = 0;
  color.store_operation = TYP_ATTACHMENT_STOREOP_NOTHING;
  color.layout_initial = TYP_IMAGE_LAYOUT_EMPTY;
  color.layout_final = TYP_IMAGE_LAYOUT_PRESENT;
  vk_attachment->color_description(color);
  vk_attachment->color_reference(color);
  subpass->vec_color.push_back(color);

  // Depth
  vk::structure::Attachment depth;
  depth.index = 1;
  depth.store_operation = TYP_ATTACHMENT_STOREOP_STORE;
  depth.layout_initial = TYP_IMAGE_LAYOUT_EMPTY;
  depth.layout_final = TYP_IMAGE_LAYOUT_DEPTH_READONLY;
  vk_attachment->depth_description(depth);
  vk_attachment->depth_reference(depth);
  subpass->depth = depth;

  //---------------------------
}

//Subfunction
void VK_subpass::create_subpass_description(vk::structure::Subpass* subpass){
  //---------------------------

  //Format elements
  uint32_t nb_color_attachment = 0;
  vector<VkAttachmentReference*> vec_color;
  for(int i=0; i<subpass->vec_color.size(); i++){
    vec_color.push_back(&subpass->vec_color[0].reference);
  }
  nb_color_attachment += subpass->vec_color.size();
  vector<VkAttachmentReference*> vec_color_resolve;
  for(int i=0; i<subpass->vec_color_resolve.size(); i++){
    vec_color_resolve.push_back(&subpass->vec_color_resolve[0].reference);
  }
  nb_color_attachment += subpass->vec_color_resolve.size();

  //Subpass decription
  VkSubpassDescription subpass_description{};
  subpass_description.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
  subpass_description.pDepthStencilAttachment = &subpass->depth.reference;
  subpass_description.colorAttachmentCount = nb_color_attachment;
  subpass_description.pColorAttachments = *vec_color.data();
  if(vec_color_resolve.size() != 0)
  subpass_description.pResolveAttachments = *vec_color_resolve.data();

  //Subpass dependencies
  VkSubpassDependency subpass_dependency{};
  subpass_dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
  subpass_dependency.dstSubpass = 0;
  subpass_dependency.srcAccessMask = 0;
  subpass_dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
  subpass_dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
  subpass_dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;

  //---------------------------
  subpass->description = subpass_description;
  subpass->dependency = subpass_dependency;
}
