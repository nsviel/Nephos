#pragma once

#include <Utility/Specific/Common.h>

namespace vk::render::edl{class Shader;}
namespace vk::render::scene{class Shader;}
namespace vk::render::edl{class Renderpass;}
namespace vk::render::scene{class Renderpass;}
namespace vk::render::gui{class Renderpass;}
namespace vk::structure{class Vulkan;}


namespace vk::render{

class Manager
{
public:
  //Constructor / Destructor
  Manager(vk::structure::Vulkan* vk_struct);
  ~Manager();

public:
  //Main functions
  void init();

  inline vk::render::edl::Shader* get_shader_edl(){return shader_edl;}
  inline vk::render::scene::Shader* get_shader_scene(){return shader_scene;}

private:
  vk::render::edl::Shader* shader_edl;
  vk::render::scene::Shader* shader_scene;

  vk::render::scene::Renderpass* rp_scene;
  vk::render::edl::Renderpass* rp_edl;
  vk::render::gui::Renderpass* rp_gui;
};

}
