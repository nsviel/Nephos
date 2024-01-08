#include "VK_attachment.h"

#include <Vulkan/VK_struct/Namespace.h>
#include <Vulkan/VK_image/VK_color.h>
#include <Vulkan/VK_image/VK_depth.h>

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
  this->vk_color = new VK_color(struct_vulkan);
  this->vk_depth = new VK_depth(struct_vulkan);

  //---------------------------
}
VK_attachment::~VK_attachment(){}

//Color attachment
void VK_attachment::color_attachment_description(vk::structure::Attachment& color){
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
void VK_attachment::color_attachment_reference(vk::structure::Attachment& color){
  //---------------------------

  VkAttachmentReference color_reference{};
  color_reference.attachment = color.index;
  color_reference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

  //---------------------------
  color.reference = color_reference;
}
void VK_attachment::color_attachment_resolve_description(vk::structure::Attachment& color_resolve){
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
void VK_attachment::color_attachment_resolve_reference(vk::structure::Attachment& color_resolve){
  //---------------------------

  VkAttachmentReference color_reference{};
  color_reference.attachment = color_resolve.index;
  color_reference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

  //---------------------------
  color_resolve.reference = color_reference;
}

//Depth attachment
void VK_attachment::depth_attachment_description(vk::structure::Attachment& depth){
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
void VK_attachment::depth_attachment_reference(vk::structure::Attachment& depth){
  //---------------------------

  VkAttachmentReference depth_reference{};
  depth_reference.attachment = depth.index;
  depth_reference.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

  //---------------------------
  depth.reference = depth_reference;
}
