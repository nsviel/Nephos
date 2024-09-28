#pragma once

namespace vk{class Structure;}
namespace vk::postprocess{class Renderpass;}
namespace vk::geometry{class Renderpass;}
namespace vk::present{class Renderpass;}


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
  void loop();

private:
  vk::Structure* vk_struct;
  vk::geometry::Renderpass* rp_scene;
  vk::postprocess::Renderpass* rp_edl;
  vk::present::Renderpass* rp_gui;
};

}
