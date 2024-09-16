#pragma once

namespace vk{class Structure;}
namespace vk::structure{class Renderpass;}
namespace vk::render::geometry{class Scene;}


namespace vk::render::geometry{

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
  vk::render::geometry::Scene* vk_scene;
};

}
