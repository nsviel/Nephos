#pragma once

namespace vk{class Structure;}
namespace vk::structure{class Renderpass;}
namespace vk::render::offscreen{class Shader;}
namespace vk::render::offscreen{class Scene;}


namespace vk::render::offscreen{

class Renderpass
{
public:
  //Constructor / Destructor
  Renderpass(vk::Structure* vk_struct, vk::render::offscreen::Shader* vk_shader);
  ~Renderpass();

public:
  //Main function
  void init();

  //Subfunction
  void create_renderpass(vk::structure::Renderpass* renderpass);

private:
  vk::Structure* vk_struct;
  vk::render::offscreen::Shader* vk_shader;
  vk::render::offscreen::Scene* vk_scene;
};

}
