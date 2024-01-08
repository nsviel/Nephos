#pragma once

#include <Utility/Specific/common.h>


namespace vk::structure{

struct Attachment{
  //---------------------------

  int index;

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
