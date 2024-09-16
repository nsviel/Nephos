#pragma once

namespace vk{class Structure;}
namespace vk::render::edl{class Renderpass;}
namespace vk::render::geometry{class Renderpass;}
namespace vk::render::onscreen{class Renderpass;}


namespace vk::render{

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
  vk::render::geometry::Renderpass* rp_scene;
  vk::render::edl::Renderpass* rp_edl;
  vk::render::onscreen::Renderpass* rp_gui;
};

}
