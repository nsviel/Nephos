#include "Subpass.h"

#include <Vulkan/VK_struct/Namespace.h>
#include <Vulkan/VK_image/VK_color.h>
#include <Vulkan/VK_image/VK_depth.h>
#include <Vulkan/VK_command/VK_command.h>

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

namespace vk{

//Constructor / Destructor
Subpass::Subpass(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_command = new VK_command(struct_vulkan);
  this->vk_color = new VK_color(struct_vulkan);
  this->vk_depth = new VK_depth(struct_vulkan);
  this->vk_attachment = new VK_attachment(struct_vulkan);

  //---------------------------
}
Subpass::~Subpass(){}

//Main function
void Subpass::create_subpass(vk::structure::Renderpass* renderpass){
  //---------------------------

  for(int i=0; i<renderpass->vec_subpass.size(); i++){
    vk::structure::Subpass* subpass = renderpass->vec_subpass[i];

    if(subpass->target == "shader"){
      this->create_subpass_shader(subpass);
    }
    else if(subpass->target == "transfert"){
      this->create_subpass_transfert(subpass);
    }
    else if(subpass->target == "presentation"){
      this->create_subpass_presentation(subpass);
    }
    else{
      cout<<"[error] subpass target not recognized"<<endl;
    }
  }

  //---------------------------
}

//Subfunction
void Subpass::create_subpass_shader(vk::structure::Subpass* subpass){
  //---------------------------



  // Color
  vk::structure::Attachment color;
  color.index = 0;
  color.load_operation = TYP_ATTACHMENT_LOADOP_CLEAR;
  color.store_operation = TYP_ATTACHMENT_STOREOP_STORE;
  color.layout_initial = TYP_IMAGE_LAYOUT_EMPTY;
  color.layout_final = TYP_IMAGE_LAYOUT_SHADER_READONLY;
  this->color_attachment_description(color);
  this->color_attachment_reference(color);
  subpass->vec_color.push_back(color);

  // Depth
  vk::structure::Attachment depth;
  depth.index = 1;
  depth.load_operation = TYP_ATTACHMENT_LOADOP_CLEAR;
  depth.store_operation = TYP_ATTACHMENT_STOREOP_STORE;
  depth.layout_initial = TYP_IMAGE_LAYOUT_EMPTY;
  depth.layout_final = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;
  this->depth_attachment_description(depth);
  this->depth_attachment_reference(depth);
  subpass->depth = depth;

  //Color resolver
  vk::structure::Attachment color_resolve;
  color_resolve.index = 1;
  this->color_attachment_resolve_description(color_resolve);
  this->color_attachment_resolve_reference(color_resolve);
  //subpass->vec_color_resolve.push_back(color_resolve);

  // Subpass description
  this->create_subpass_description(subpass);

  //---------------------------
}
void Subpass::create_subpass_transfert(vk::structure::Subpass* subpass){
  //---------------------------

  // Depth
  vk::structure::Attachment depth;
  depth.index = 1;
  depth.load_operation = TYP_ATTACHMENT_LOADOP_CLEAR;
  depth.store_operation = TYP_ATTACHMENT_STOREOP_STORE;
  depth.layout_initial = TYP_IMAGE_LAYOUT_EMPTY;
  depth.layout_final = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;
  this->depth_attachment_description(depth);
  this->depth_attachment_reference(depth);
  subpass->depth = depth;

  // Color
  vk::structure::Attachment color;
  color.index = 0;
  color.load_operation = TYP_ATTACHMENT_LOADOP_CLEAR;
  color.store_operation = TYP_ATTACHMENT_STOREOP_STORE;
  color.layout_initial = TYP_IMAGE_LAYOUT_EMPTY;
  color.layout_final = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
  this->color_attachment_description(color);
  this->color_attachment_reference(color);
  subpass->vec_color.push_back(color);

  // Subpass description
  this->create_subpass_description(subpass);

  //---------------------------
}
void Subpass::create_subpass_presentation(vk::structure::Subpass* subpass){
  //---------------------------



  // Color
  vk::structure::Attachment color;
  color.index = 0;
  color.load_operation = TYP_ATTACHMENT_LOADOP_CLEAR;
  color.store_operation = TYP_ATTACHMENT_STOREOP_NOTHING;
  color.layout_initial = TYP_IMAGE_LAYOUT_EMPTY;
  color.layout_final = TYP_IMAGE_LAYOUT_PRESENT;
  this->color_attachment_description(color);
  this->color_attachment_reference(color);
  subpass->vec_color.push_back(color);

  // Depth
  vk::structure::Attachment depth;
  depth.index = 1;
  depth.load_operation = TYP_ATTACHMENT_LOADOP_CLEAR;
  depth.store_operation = TYP_ATTACHMENT_STOREOP_NOTHING;
  depth.layout_initial = TYP_IMAGE_LAYOUT_EMPTY;
  depth.layout_final = TYP_IMAGE_LAYOUT_DEPTH_READONLY;
  this->depth_attachment_description(depth);
  this->depth_attachment_reference(depth);
  subpass->depth = depth;

  // Subpass description
  this->create_subpass_description(subpass);

  //---------------------------
}
void Subpass::create_subpass_description(vk::structure::Subpass* subpass){
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

//Color attachment
void Subpass::color_attachment_description(vk::structure::Attachment& color){
  //---------------------------

  VkAttachmentDescription color_description{};
  color_description.format = vk_color->find_color_format();
  color_description.samples = struct_vulkan->device.struct_device.max_sample_count;
  color_description.loadOp = color.load_operation;
  color_description.storeOp = color.store_operation;
  color_description.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  color_description.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  color_description.initialLayout = color.layout_initial;
  color_description.finalLayout = color.layout_final;

  //---------------------------
  color.description = color_description;
}
void Subpass::color_attachment_reference(vk::structure::Attachment& color){
  //---------------------------

  VkAttachmentReference color_reference{};
  color_reference.attachment = color.index;
  color_reference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

  //---------------------------
  color.reference = color_reference;
}
void Subpass::color_attachment_resolve_description(vk::structure::Attachment& color_resolve){
  //---------------------------

  VkAttachmentDescription color_description{};
  color_description.format = vk_color->find_color_format();
  color_description.samples = VK_SAMPLE_COUNT_1_BIT;
  color_description.loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  color_description.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
  color_description.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  color_description.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  color_description.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  color_description.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

  //---------------------------
  color_resolve.description = color_description;
}
void Subpass::color_attachment_resolve_reference(vk::structure::Attachment& color_resolve){
  //---------------------------

  VkAttachmentReference color_reference{};
  color_reference.attachment = color_resolve.index;
  color_reference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

  //---------------------------
  color_resolve.reference = color_reference;
}

//Depth attachment
void Subpass::depth_attachment_description(vk::structure::Attachment& depth){
  //---------------------------

  VkAttachmentDescription depth_attachment{};
  depth_attachment.format = vk_depth->find_depth_format();
  depth_attachment.samples = struct_vulkan->device.struct_device.max_sample_count;
  depth_attachment.loadOp = depth.load_operation;
  depth_attachment.storeOp = depth.store_operation;
  depth_attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  depth_attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  depth_attachment.initialLayout = depth.layout_initial;
  depth_attachment.finalLayout = depth.layout_final;

  //---------------------------
  depth.description = depth_attachment;
}
void Subpass::depth_attachment_reference(vk::structure::Attachment& depth){
  //---------------------------

  VkAttachmentReference depth_reference{};
  depth_reference.attachment = depth.index;
  depth_reference.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

  //---------------------------
  depth.reference = depth_reference;
}

}
