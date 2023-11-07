#ifndef STRUCT_SUBPASS_H
#define STRUCT_SUBPASS_H

#include <ELE_specific/common.h>


struct Struct_subpass_attachment{
  //---------------------------

  int item;

  //Attachment info
  VkAttachmentLoadOp load_operation;
  VkAttachmentStoreOp store_operation;

  //Attachment image layout
  VkImageLayout layout_initial;
  VkImageLayout layout_final;

  //---------------------------
};

struct Struct_subpass{
  //---------------------------

  //Subpass info
  VkSubpassDescription description;
  VkSubpassDependency dependency;
  VkAttachmentReference depth_reference;

  //Attachment
  Struct_subpass_attachment color;
  Struct_subpass_attachment depth;
  std::vector<VkAttachmentReference> vec_color_reference;
  std::vector<VkAttachmentDescription> vec_attachment_description;

  //---------------------------
};


#endif
