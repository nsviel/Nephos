#pragma once

#include <string>

namespace vk{class Structure;}
namespace vk::pipeline{class Pipeline;}
namespace vk::structure{class Renderpass;}
namespace vk::structure{class Pipeline;}
namespace vk::renderpass{class Renderpass;}
namespace vk::synchro{class Synchro;}
namespace vk::gui{class Render;}


namespace vk::shader{

class Reloader
{
public:
  //Constructor / Destructor
  Reloader(vk::Structure* vk_struct);
  ~Reloader();

public:
  //Main function
  void hot_shader_reload();

  //Subfunction
  void reload_renderpass(vk::structure::Renderpass& renderpass);

private:
  vk::Structure* vk_struct;
  vk::pipeline::Pipeline* vk_pipeline;
  vk::synchro::Synchro* vk_synchro;
  vk::renderpass::Renderpass* vk_renderpass;
  vk::gui::Render* vk_render;
};

}
