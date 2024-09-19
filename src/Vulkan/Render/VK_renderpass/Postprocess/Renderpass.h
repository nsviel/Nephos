#pragma once

namespace vk{class Structure;}
namespace vk::postprocess::subpass{class EDL;}
namespace vk::structure{class Renderpass;}


namespace vk::postprocess{

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
  vk::postprocess::subpass::EDL* vk_edl;
};

}
