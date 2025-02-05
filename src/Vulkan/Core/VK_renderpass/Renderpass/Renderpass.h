#pragma once

namespace vk{class Structure;}
namespace vk::pipeline::gfx{class Pipeline;}
namespace vk::renderpass{class Framebuffer;}
namespace vk::renderpass{class Subpass;}
namespace vk::renderpass{class Attachment;}
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
  void init_renderpass(vk::structure::Renderpass& renderpass);
  void attachment_renderpass(vk::structure::Renderpass& renderpass);
  void create_renderpass(vk::structure::Renderpass& renderpass);
  void clean_renderpass(vk::structure::Renderpass& renderpass);
  void clean_framebuffer();
  void create_framebuffer();
  void update_sampler();

private:
  vk::Structure* vk_struct;
  vk::pipeline::gfx::Pipeline* vk_pipeline;
  vk::renderpass::Subpass* vk_subpass;
  vk::renderpass::Framebuffer* vk_framebuffer;
  vk::renderpass::Attachment* vk_attachment;
};

}
