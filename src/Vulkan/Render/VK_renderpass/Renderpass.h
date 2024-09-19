#pragma once

namespace vk{class Structure;}
namespace vk::postprocess{class Renderpass;}
namespace vk::render::geometry{class Renderpass;}
namespace vk::present{class Renderpass;}


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
  vk::postprocess::Renderpass* rp_edl;
  vk::present::Renderpass* rp_gui;
};

}
