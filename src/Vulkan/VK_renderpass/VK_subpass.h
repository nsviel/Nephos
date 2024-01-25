#pragma once

#include <Utility/Specific/common.h>

class VK_command;
class VK_attachment;
namespace vk::structure{class Vulkan;}
namespace vk::structure{class Renderpass;}
namespace vk::structure{class Subpass;}


class VK_subpass
{
public:
  //Constructor / Destructor
  VK_subpass(vk::structure::Vulkan* struct_vulkan);
  ~VK_subpass();

public:
  //Main functions
  void create_subpass(vk::structure::Renderpass* renderpass);

  //Subpass type
  void create_subpass_shader(vk::structure::Subpass* subpass);
  void create_subpass_transfert(vk::structure::Subpass* subpass);
  void create_subpass_presentation(vk::structure::Subpass* subpass);

  //Subfunction
  void create_subpass_description(vk::structure::Subpass* subpass);

private:
  vk::structure::Vulkan* struct_vulkan;
  VK_command* vk_command;
  VK_attachment* vk_attachment;
};
