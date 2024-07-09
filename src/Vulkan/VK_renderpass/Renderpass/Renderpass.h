#pragma once

namespace vk::renderpass{class Pipeline;}
namespace vk::renderpass{class Framebuffer;}
namespace vk::renderpass{class Subpass;}
namespace vk{class Structure;}
namespace vk::structure{class Renderpass;}


namespace vk::renderpass{

class Renderpass
{
public:
  //Constructor / Destructor
  Renderpass(vk::Structure* vk_struct);
  ~Renderpass();

public:
  //Main function
  void init();
  void clean();

  //Subfunction
  void init_renderpass(vk::structure::Renderpass* renderpass);
  void create_renderpass(vk::structure::Renderpass* renderpass);
  void clean_renderpass(vk::structure::Renderpass* renderpass);

private:
  vk::Structure* vk_struct;
  vk::renderpass::Pipeline* vk_pipeline;
  vk::renderpass::Subpass* vk_subpass;
  vk::renderpass::Framebuffer* vk_framebuffer;
};

}
