#pragma once

namespace vk{class Structure;}
namespace vk::gfx::canvas{class Subpass;}
namespace vk::structure{class Renderpass;}


namespace vk::gfx::presentation{

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
  vk::gfx::canvas::Subpass* vk_subpass;
};

}
