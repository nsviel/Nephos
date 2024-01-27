#pragma once

#include <Utility/Specific/common.h>

namespace vk::renderpass{class Pipeline;}
namespace vk::structure{class Vulkan;}
namespace vk::structure{class Renderpass;}
namespace vk::structure{class Pipeline;}


namespace vk::shader{

class Reloader
{
public:
  //Constructor / Destructor
  Reloader(vk::structure::Vulkan* struct_vulkan);
  ~Reloader();

public:
  //Main function
  void hot_shader_reload(string shader_1, string shader_2);
  void recreate_pipeline(vk::structure::Renderpass* renderpass, vk::structure::Pipeline* pipeline);

private:
  vk::structure::Vulkan* struct_vulkan;
  vk::renderpass::Pipeline* vk_pipeline;
};

}
