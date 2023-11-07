#include "VK_subpass.h"

#include <VK_main/VK_engine.h>
#include <VK_struct/Struct_vulkan.h>
#include <VK_image/VK_color.h>
#include <VK_image/VK_depth.h>


//Constructor / Destructor
VK_subpass::VK_subpass(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->struct_vulkan = vk_engine->get_struct_vulkan();
  this->vk_color = new VK_color(vk_engine);
  this->vk_depth = new VK_depth(vk_engine);

  //---------------------------
}
VK_subpass::~VK_subpass(){}

//Main function
void VK_subpass::create_subpass(Struct_renderpass* renderpass){
  //---------------------------

  if(renderpass->subpass_trg == "shader"){
    this->create_subpass_shader(renderpass);
  }
  else if(renderpass->subpass_trg == "presentation"){
    this->create_subpass_presentation(renderpass);
  }

  //---------------------------
}
void VK_subpass::create_subpass_shader(Struct_renderpass* renderpass){
  Struct_subpass* subpass = new Struct_subpass();
  //---------------------------

  // Color
  subpass->color.item = 0;
  subpass->color.load_operation = ATTACHMENT_LOADOP_CLEAR;
  subpass->color.store_operation = ATTACHMENT_STOREOP_STORE;
  subpass->color.layout_initial = IMAGE_LAYOUT_EMPTY;
  subpass->color.layout_final = IMAGE_LAYOUT_SHADER_READONLY;
  this->color_attachment_description(subpass);
  this->color_attachment_reference(subpass);

  // Depth
  subpass->depth.item = 1;
  subpass->depth.load_operation = ATTACHMENT_LOADOP_CLEAR;
  subpass->depth.store_operation = ATTACHMENT_STOREOP_STORE;
  subpass->depth.layout_initial = IMAGE_LAYOUT_EMPTY;
  subpass->depth.layout_final = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;
  this->depth_attachment_description(subpass);
  this->depth_attachment_reference(subpass);

  this->create_subpass_description(subpass);
  renderpass->vec_subpass.push_back(subpass);

  //---------------------------
}
void VK_subpass::create_subpass_presentation(Struct_renderpass* renderpass){
  Struct_subpass* subpass = new Struct_subpass();
  //---------------------------

  // Color
  subpass->color.item = 0;
  subpass->color.load_operation = ATTACHMENT_LOADOP_CLEAR;
  subpass->color.store_operation = ATTACHMENT_STOREOP_NOTHING;
  subpass->color.layout_initial = IMAGE_LAYOUT_EMPTY;
  subpass->color.layout_final = IMAGE_LAYOUT_PRESENT;
  this->color_attachment_description(subpass);
  this->color_attachment_reference(subpass);

  // Depth
  subpass->depth.item = 1;
  subpass->depth.load_operation = ATTACHMENT_LOADOP_CLEAR;
  subpass->depth.store_operation = ATTACHMENT_STOREOP_NOTHING;
  subpass->depth.layout_initial = IMAGE_LAYOUT_EMPTY;
  subpass->depth.layout_final = IMAGE_LAYOUT_DEPTH_ATTACHMENT;
  this->depth_attachment_description(subpass);
  this->depth_attachment_reference(subpass);

  this->create_subpass_description(subpass);
  renderpass->vec_subpass.push_back(subpass);

  //---------------------------
}

//Subfunction
void VK_subpass::color_attachment_description(Struct_subpass* subpass){
  //---------------------------

  VkAttachmentDescription color_description{};
  color_description.format = vk_color->find_color_format();
  color_description.samples = VK_SAMPLE_COUNT_1_BIT;
  color_description.loadOp = subpass->color.load_operation;
  color_description.storeOp = subpass->color.store_operation;
  color_description.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  color_description.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  color_description.initialLayout = subpass->color.layout_initial;
  color_description.finalLayout = subpass->color.layout_final;
  subpass->vec_description.push_back(color_description);

  //---------------------------
}
void VK_subpass::color_attachment_reference(Struct_subpass* subpass){
  //---------------------------

  VkAttachmentReference color_reference{};
  color_reference.attachment = subpass->color.item;
  color_reference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
  subpass->color.reference = color_reference;;

  //---------------------------
}
void VK_subpass::depth_attachment_description(Struct_subpass* subpass){
  //---------------------------

  VkAttachmentDescription depth_attachment{};
  depth_attachment.format = vk_depth->find_depth_format();
  depth_attachment.samples = VK_SAMPLE_COUNT_1_BIT;
  depth_attachment.loadOp = subpass->depth.load_operation;
  depth_attachment.storeOp = subpass->depth.store_operation;
  depth_attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  depth_attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  depth_attachment.initialLayout = subpass->depth.layout_initial;
  depth_attachment.finalLayout = subpass->depth.layout_final;
  subpass->vec_description.push_back(depth_attachment);

  //---------------------------
}
void VK_subpass::depth_attachment_reference(Struct_subpass* subpass){
  //---------------------------

  VkAttachmentReference depth_attachment_ref{};
  depth_attachment_ref.attachment = subpass->depth.item;
  depth_attachment_ref.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
  subpass->depth.reference = depth_attachment_ref;

  //---------------------------
}
void VK_subpass::create_subpass_description(Struct_subpass* subpass){
  //---------------------------

  //Subpasses
  VkSubpassDescription subpass_description{};
  subpass_description.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
  subpass_description.colorAttachmentCount = 1;
  subpass_description.pColorAttachments = &subpass->color.reference;
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
