#include "VK_subpass.h"

#include <VK_main/VK_engine.h>
#include <VK_main/Struct_vulkan.h>
#include <VK_image/VK_color.h>
#include <VK_image/VK_depth.h>
#include <VK_command/VK_command_buffer.h>


//Constructor / Destructor
VK_subpass::VK_subpass(Struct_vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_command_buffer = new VK_command_buffer(struct_vulkan);
  this->vk_color = new VK_color(struct_vulkan);
  this->vk_depth = new VK_depth(struct_vulkan);

  //---------------------------
}
VK_subpass::~VK_subpass(){}

//Main function
void VK_subpass::create_subpass(Struct_renderpass* renderpass){
  //---------------------------

  for(int i=0; i<renderpass->vec_subpass.size(); i++){
    Struct_subpass* subpass = renderpass->vec_subpass[i];

    vk_command_buffer->allocate_command_buffer_primary(subpass);
    if(subpass->target == "shader"){
      this->create_subpass_shader(subpass);
    }
    else if(subpass->target == "presentation"){
      this->create_subpass_presentation(subpass);
    }
  }

  //---------------------------
}

//Subfunction
void VK_subpass::create_subpass_shader(Struct_subpass* subpass){
  //---------------------------

  // Color
  Struct_attachment color;
  color.item = 0;
  color.load_operation = ATTACHMENT_LOADOP_CLEAR;
  color.store_operation = ATTACHMENT_STOREOP_STORE;
  color.layout_initial = IMAGE_LAYOUT_EMPTY;
  color.layout_final = IMAGE_LAYOUT_SHADER_READONLY;
  this->color_attachment_description(color);
  this->color_attachment_reference(color);
  subpass->vec_color.push_back(color);

  // Depth
  Struct_attachment depth;
  depth.item = 1;
  depth.load_operation = ATTACHMENT_LOADOP_CLEAR;
  depth.store_operation = ATTACHMENT_STOREOP_STORE;
  depth.layout_initial = IMAGE_LAYOUT_EMPTY;
  depth.layout_final = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;
  this->depth_attachment_description(depth);
  this->depth_attachment_reference(depth);
  subpass->depth = depth;

  // Subpass description
  this->create_subpass_description(subpass);

  //---------------------------
}
void VK_subpass::create_subpass_presentation(Struct_subpass* subpass){
  //---------------------------

  // Color
  Struct_attachment color;
  color.item = 0;
  color.load_operation = ATTACHMENT_LOADOP_CLEAR;
  color.store_operation = ATTACHMENT_STOREOP_NOTHING;
  color.layout_initial = IMAGE_LAYOUT_EMPTY;
  color.layout_final = IMAGE_LAYOUT_PRESENT;
  this->color_attachment_description(color);
  this->color_attachment_reference(color);
  subpass->vec_color.push_back(color);

  // Depth
  Struct_attachment depth;
  depth.item = 1;
  depth.load_operation = ATTACHMENT_LOADOP_CLEAR;
  depth.store_operation = ATTACHMENT_STOREOP_NOTHING;
  depth.layout_initial = IMAGE_LAYOUT_EMPTY;
  depth.layout_final = IMAGE_LAYOUT_DEPTH_READONLY;
  this->depth_attachment_description(depth);
  this->depth_attachment_reference(depth);
  subpass->depth = depth;

  // Subpass description
  this->create_subpass_description(subpass);

  //---------------------------
}
void VK_subpass::create_subpass_description(Struct_subpass* subpass){
  //---------------------------

  //Pointer vector of all color references
  vector<VkAttachmentReference*> vec_reference;
  for(int i=0; i<subpass->vec_color.size(); i++){
    vec_reference.push_back(&subpass->vec_color[0].reference);
  }

  //Subpasses
  VkSubpassDescription subpass_description{};
  subpass_description.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
  subpass_description.colorAttachmentCount = static_cast<uint32_t>(vec_reference.size());
  subpass_description.pColorAttachments = *vec_reference.data();
  subpass_description.pDepthStencilAttachment = &subpass->depth.reference;

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
void VK_subpass::color_attachment_description(Struct_attachment& color){
  //---------------------------

  VkAttachmentDescription color_description{};
  color_description.format = vk_color->find_color_format();
  color_description.samples = VK_SAMPLE_COUNT_1_BIT;
  color_description.loadOp = color.load_operation;
  color_description.storeOp = color.store_operation;
  color_description.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  color_description.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  color_description.initialLayout = color.layout_initial;
  color_description.finalLayout = color.layout_final;
  color.description = color_description;

  //---------------------------
}
void VK_subpass::color_attachment_reference(Struct_attachment& color){
  //---------------------------

  VkAttachmentReference color_reference{};
  color_reference.attachment = color.item;
  color_reference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
  color.reference = color_reference;

  //---------------------------
}

//Depth attachment
void VK_subpass::depth_attachment_description(Struct_attachment& depth){
  //---------------------------

  VkAttachmentDescription depth_attachment{};
  depth_attachment.format = vk_depth->find_depth_format();
  depth_attachment.samples = VK_SAMPLE_COUNT_1_BIT;
  depth_attachment.loadOp = depth.load_operation;
  depth_attachment.storeOp = depth.store_operation;
  depth_attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  depth_attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  depth_attachment.initialLayout = depth.layout_initial;
  depth_attachment.finalLayout = depth.layout_final;
  depth.description = depth_attachment;

  //---------------------------
}
void VK_subpass::depth_attachment_reference(Struct_attachment& depth){
  //---------------------------

  VkAttachmentReference depth_reference{};
  depth_reference.attachment = depth.item;
  depth_reference.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
  depth.reference = depth_reference;

  //---------------------------
}
