#include "Attachment.h"

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

//Color attachment
void Attachment::color_description(vk::structure::Attachment& color){
  //---------------------------

  VkAttachmentDescription description{};
  description.format = vk_color->find_color_format();
  description.samples = vk_struct->device.physical_device.max_sample_count;
  description.loadOp = TYP_ATTACHMENT_LOADOP_CLEAR;
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
  description.samples = vk_struct->device.physical_device.max_sample_count;
  description.loadOp = TYP_ATTACHMENT_LOADOP_CLEAR;
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
