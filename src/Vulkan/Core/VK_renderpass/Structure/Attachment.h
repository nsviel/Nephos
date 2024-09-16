#pragma once

#include <vulkan/vulkan.h>


namespace vk::structure{

struct Attachment{
  //---------------------------

  int index = -1;

  //Attachment info
  VkAttachmentLoadOp load_operation = VK_ATTACHMENT_LOAD_OP_LOAD;
  VkAttachmentStoreOp store_operation = VK_ATTACHMENT_STORE_OP_STORE;
  VkAttachmentReference reference = {};
  VkAttachmentDescription description = {};

  //Attachment image layout
  VkImageLayout layout_initial = VK_IMAGE_LAYOUT_UNDEFINED;
  VkImageLayout layout_final = VK_IMAGE_LAYOUT_UNDEFINED;

  //---------------------------
};

}
