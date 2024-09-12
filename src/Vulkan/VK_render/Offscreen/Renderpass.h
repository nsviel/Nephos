#pragma once

namespace vk{class Structure;}
namespace vk::structure{class Renderpass;}
namespace vk::render::offscreen{class Scene;}
namespace vk::render::offscreen{class EDL;}


namespace vk::render::offscreen{

class Renderpass
{
public:
  //Constructor / Destructor
  Renderpass(vk::Structure* vk_struct);
  ~Renderpass();

public:
  //Main function
  void init();

private:
  vk::Structure* vk_struct;
  vk::render::offscreen::Scene* vk_scene;
  vk::render::offscreen::EDL* vk_edl;
};

}
