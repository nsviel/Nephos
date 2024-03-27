#pragma once

#include <Utility/Specific/Common.h>

namespace vk::renderpass{class Attachment;}
namespace vk::structure{class Vulkan;}
namespace vk::structure{class Renderpass;}
namespace vk::structure{class Subpass;}


namespace vk::renderpass{

class Subpass
{
public:
  //Constructor / Destructor
  Subpass(vk::structure::Vulkan* struct_vulkan);
  ~Subpass();

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
  vk::renderpass::Attachment* vk_attachment;
};

}
