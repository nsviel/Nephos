#pragma once

#include <string>

namespace vk::renderpass{class Pipeline;}
namespace vk::structure{class Vulkan;}
namespace vk::structure{class Renderpass;}
namespace vk::structure{class Pipeline;}
namespace vk::synchro{class Synchro;}


namespace vk::shader{

class Reloader
{
public:
  //Constructor / Destructor
  Reloader(vk::structure::Vulkan* vk_struct);
  ~Reloader();

public:
  //Main function
  void hot_shader_reload(std::string shader_1, std::string shader_2);
  void recreate_pipeline(vk::structure::Renderpass* renderpass, vk::structure::Pipeline* pipeline);

private:
  vk::structure::Vulkan* vk_struct;
  vk::renderpass::Pipeline* vk_pipeline;
  vk::synchro::Synchro* vk_synchro;
};

}
