#pragma once

namespace vk::renderpass{class Attachment;}
namespace vk::structure{class Vulkan;}
namespace vk::structure{class Renderpass;}
namespace vk::structure{class Subpass;}


namespace vk::renderpass{

class Subpass
{
public:
  //Constructor / Destructor
  Subpass(vk::structure::Vulkan* vk_struct);
  ~Subpass();

public:
  //Main function
  void create_subpass(vk::structure::Renderpass* renderpass);

  //Subpass type
  void create_subpass_shader(vk::structure::Subpass* subpass);
  void create_subpass_transfert(vk::structure::Subpass* subpass);
  void create_subpass_presentation(vk::structure::Subpass* subpass);

  //Subfunction
  void create_subpass_description(vk::structure::Subpass* subpass);

private:
  vk::structure::Vulkan* vk_struct;
  vk::renderpass::Attachment* vk_attachment;
};

}
