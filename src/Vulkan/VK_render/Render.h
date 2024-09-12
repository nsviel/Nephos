#pragma once

namespace vk{class Structure;}
namespace vk::render::edl{class Shader;}
namespace vk::render::offscreen{class Shader;}
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

  inline vk::render::edl::Shader* get_shader_edl(){return shader_edl;}
  inline vk::render::offscreen::Shader* get_shader_scene(){return shader_scene;}

private:
  vk::Structure* vk_struct;
  vk::render::edl::Shader* shader_edl;
  vk::render::offscreen::Shader* shader_scene;

  vk::render::offscreen::Renderpass* rp_scene;
  vk::render::edl::Renderpass* rp_edl;
  vk::render::onscreen::Renderpass* rp_gui;
};

}
