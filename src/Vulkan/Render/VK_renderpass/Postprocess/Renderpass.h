#pragma once

namespace vk{class Structure;}
namespace vk::subpass::edl{class EDL;}
namespace vk::structure{class Renderpass;}


namespace vk::render::edl{

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
  vk::subpass::edl::EDL* vk_edl;
};

}
