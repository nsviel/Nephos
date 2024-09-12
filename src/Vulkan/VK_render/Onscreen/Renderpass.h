#pragma once

namespace vk{class Structure;}
namespace vk::render::onscreen{class Subpass;}
namespace vk::structure{class Renderpass;}


namespace vk::render::onscreen{

class Renderpass
{
public:
  //Constructor / Destructor
  Renderpass(vk::Structure* vk_struct);
  ~Renderpass();

public:
  //Main function
  void init();

  //Init function
  void create_renderpass(vk::structure::Renderpass* renderpass);

private:
  vk::Structure* vk_struct;
  vk::render::onscreen::Subpass* vk_subpass;
};

}
