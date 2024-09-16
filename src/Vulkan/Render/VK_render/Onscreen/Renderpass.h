#pragma once

namespace vk{class Structure;}
namespace vk::render::onscreen{class Canvas;}
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

private:
  vk::Structure* vk_struct;
  vk::render::onscreen::Canvas* vk_subpass;
};

}
