#include "Attachment.h"

#include <Vulkan/Namespace.h>


namespace vk::renderpass{

//Constructor / Destructor
Attachment::Attachment(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_color = new vk::image::Color(vk_struct);
  this->vk_depth = new vk::image::Depth(vk_struct);

  //---------------------------
}
Attachment::~Attachment(){}

//Main function
void Attachment::attachment_shader(vk::structure::Renderpass& renderpass){
  //---------------------------

  // Color
  vk::structure::Attachment color;
  color.index = vk::attachment::COLOR;
  color.layout_final = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
  this->color_description(color);
  this->color_reference(color);
  renderpass.attachment.vec_color.push_back(color);
  renderpass.attachment.vec_color_ref.push_back(color.reference);
  renderpass.attachment.vec_description.push_back(color.description);

  // Depth
  vk::structure::Attachment depth;
  depth.index = vk::attachment::DEPTH;
  depth.layout_final = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;
  this->depth_description(depth);
  this->depth_reference(depth);
  renderpass.attachment.depth = depth;
  renderpass.attachment.vec_description.push_back(depth.description);

  // Color resolver
  vk::structure::Attachment color_resolve;
  color_resolve.index = vk::attachment::COLOR;
  color_resolve.layout_final = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
  this->color_resolve_description(color_resolve);
  this->color_resolve_reference(color_resolve);
  //renderpass.attachment.vec_color_resolve.push_back(color_resolve);
  //renderpass.attachment.vec_color_resolve_ref.push_back(&color_resolve.reference);

  //---------------------------
}
void Attachment::attachment_transfert(vk::structure::Renderpass& renderpass){
  //---------------------------

  // Color
  vk::structure::Attachment color;
  color.index = vk::attachment::COLOR;
  color.layout_final = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
  this->color_description(color);
  this->color_reference(color);
  renderpass.attachment.vec_color.push_back(color);
  renderpass.attachment.vec_color_ref.push_back(color.reference);
  renderpass.attachment.vec_description.push_back(color.description);

  // Depth
  vk::structure::Attachment depth;
  depth.index = vk::attachment::DEPTH;
  depth.layout_final = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;
  this->depth_description(depth);
  this->depth_reference(depth);
  renderpass.attachment.depth = depth;
  renderpass.attachment.vec_description.push_back(depth.description);

  //---------------------------
}
void Attachment::attachment_presentation(vk::structure::Renderpass& renderpass){
  //---------------------------

  // Color
  vk::structure::Attachment color;
  color.index = vk::attachment::COLOR;
  color.layout_final = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
  this->color_description(color);
  this->color_reference(color);
  renderpass.attachment.vec_color.push_back(color);
  renderpass.attachment.vec_color_ref.push_back(color.reference);
  renderpass.attachment.vec_description.push_back(color.description);

  // Depth
  vk::structure::Attachment depth;
  depth.index = vk::attachment::DEPTH;
  depth.layout_final = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;
  this->depth_description(depth);
  this->depth_reference(depth);
  renderpass.attachment.depth = depth;
  renderpass.attachment.vec_description.push_back(depth.description);
  
  //---------------------------
}

//Color attachment
void Attachment::color_description(vk::structure::Attachment& color){
  //---------------------------

  VkAttachmentDescription description{};
  description.format = vk_color->find_color_format();
  description.samples = vk_struct->core.device.physical_device.max_sample_count;
  description.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
  description.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
  description.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  description.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  description.initialLayout = TYP_IMAGE_LAYOUT_EMPTY;
  description.finalLayout = color.layout_final;

  //---------------------------
  color.description = description;
}
void Attachment::color_reference(vk::structure::Attachment& color){
  //---------------------------

  VkAttachmentReference reference{};
  reference.attachment = color.index;
  reference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

  //---------------------------
  color.reference = reference;
}
void Attachment::color_resolve_description(vk::structure::Attachment& color_resolve){
  //---------------------------

  VkAttachmentDescription description{};
  description.format = vk_color->find_color_format();
  description.samples = VK_SAMPLE_COUNT_1_BIT;
  description.loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  description.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
  description.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  description.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  description.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  description.finalLayout = color_resolve.layout_final;

  //---------------------------
  color_resolve.description = description;
}
void Attachment::color_resolve_reference(vk::structure::Attachment& color_resolve){
  //---------------------------

  VkAttachmentReference reference{};
  reference.attachment = color_resolve.index;
  reference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

  //---------------------------
  color_resolve.reference = reference;
}

//Depth attachment
void Attachment::depth_description(vk::structure::Attachment& depth){
  //---------------------------

  VkAttachmentDescription description{};
  description.format = vk_depth->find_depth_format();
  description.samples = vk_struct->core.device.physical_device.max_sample_count;
  description.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
  description.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
  description.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  description.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  description.initialLayout = TYP_IMAGE_LAYOUT_EMPTY;
  description.finalLayout = depth.layout_final;

  //---------------------------
  depth.description = description;
}
void Attachment::depth_reference(vk::structure::Attachment& depth){
  //---------------------------

  VkAttachmentReference reference{};
  reference.attachment = depth.index;
  reference.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

  //---------------------------
  depth.reference = reference;
}

}
