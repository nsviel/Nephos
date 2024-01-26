#include "VK_attachment.h"

#include <Vulkan/Namespace.h>

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
VK_attachment::VK_attachment(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_color = new vk::image::Color(struct_vulkan);
  this->vk_depth = new vk::image::VK_depth(struct_vulkan);

  //---------------------------
}
VK_attachment::~VK_attachment(){}

//Color attachment
void VK_attachment::color_description(vk::structure::Attachment& color){
  //---------------------------

  VkAttachmentDescription description{};
  description.format = vk_color->find_color_format();
  description.samples = struct_vulkan->device.physical_device.max_sample_count;
  description.loadOp = TYP_ATTACHMENT_LOADOP_CLEAR;
  description.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
  description.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  description.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  description.initialLayout = TYP_IMAGE_LAYOUT_EMPTY;
  description.finalLayout = color.layout_final;

  //---------------------------
  color.description = description;
}
void VK_attachment::color_reference(vk::structure::Attachment& color){
  //---------------------------

  VkAttachmentReference reference{};
  reference.attachment = color.index;
  reference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

  //---------------------------
  color.reference = reference;
}
void VK_attachment::color_resolve_description(vk::structure::Attachment& color_resolve){
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
void VK_attachment::color_resolve_reference(vk::structure::Attachment& color_resolve){
  //---------------------------

  VkAttachmentReference reference{};
  reference.attachment = color_resolve.index;
  reference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

  //---------------------------
  color_resolve.reference = reference;
}

//Depth attachment
void VK_attachment::depth_description(vk::structure::Attachment& depth){
  //---------------------------

  VkAttachmentDescription description{};
  description.format = vk_depth->find_depth_format();
  description.samples = struct_vulkan->device.physical_device.max_sample_count;
  description.loadOp = TYP_ATTACHMENT_LOADOP_CLEAR;
  description.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
  description.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  description.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  description.initialLayout = TYP_IMAGE_LAYOUT_EMPTY;
  description.finalLayout = depth.layout_final;

  //---------------------------
  depth.description = description;
}
void VK_attachment::depth_reference(vk::structure::Attachment& depth){
  //---------------------------

  VkAttachmentReference reference{};
  reference.attachment = depth.index;
  reference.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

  //---------------------------
  depth.reference = reference;
}
