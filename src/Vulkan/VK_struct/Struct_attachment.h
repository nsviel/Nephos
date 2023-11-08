#ifndef STRUCT_ATTACHMENT_H
#define STRUCT_ATTACHMENT_H

#include <ELE_specific/common.h>


struct Struct_attachment{
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


#endif
