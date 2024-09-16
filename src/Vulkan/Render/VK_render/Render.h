#pragma once

namespace vk{class Structure;}
namespace vk::render::edl{class Renderpass;}
namespace vk::render::offscreen{class Renderpass;}
namespace vk::render::onscreen{class Renderpass;}


namespace vk::render{

class Render
{
public:
  //Constructor / Destructor
  Render(vk::Structure* vk_struct);
  ~Render();

public:
  //Main function
  void init();

private:
  vk::Structure* vk_struct;
  vk::render::offscreen::Renderpass* rp_scene;
  vk::render::edl::Renderpass* rp_edl;
  vk::render::onscreen::Renderpass* rp_gui;
};

}
