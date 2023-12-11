#pragma once

#include <UTL_specific/common.h>


namespace vk::structure{

struct Struct_vk_attachment{
  //---------------------------

  int item;

  //Attachment info
  VkAttachmentLoadOp load_operation;
  VkAttachmentStoreOp store_operation;
  VkAttachmentReference reference;
  VkAttachmentDescription description;

  //Attachment image layout
  VkImageLayout layout_initial;
  VkImageLayout layout_final;

  //---------------------------
};

}
