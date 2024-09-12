#pragma once

#include <Vulkan/VK_render/Offscreen/Shader.h>

namespace vk{class Structure;}
namespace vk::structure{class Renderpass;}
namespace vk::render::offscreen{class Shader;}
namespace vk::render::offscreen{class Drawer;}
namespace vk::render::pipeline{class Topology;}


namespace vk::render::offscreen{

class Scene
{
public:
  //Constructor / Destructor
  Scene(vk::Structure* vk_struct, vk::render::offscreen::Shader* vk_shader);
  ~Scene();

public:
  //Main function
  void create_subpass(vk::structure::Renderpass* renderpass);

private:
  vk::Structure* vk_struct;
  vk::render::pipeline::Topology* vk_pipeline;
  vk::render::offscreen::Drawer* vk_drawer;
};

}
