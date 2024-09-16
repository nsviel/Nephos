#pragma once

namespace vk{class Structure;}
namespace vk::render::edl{class EDL;}
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

  //Init functions
  void create_renderpass(vk::structure::Renderpass& renderpass);

private:
  vk::Structure* vk_struct;
  vk::render::edl::EDL* vk_edl;
};

}
