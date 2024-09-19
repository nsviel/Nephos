#pragma once

namespace vk{class Structure;}
namespace vk::present::subpass{class Canvas;}
namespace vk::structure{class Renderpass;}


namespace vk::present{

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
  vk::present::subpass::Canvas* vk_subpass;
};

}
