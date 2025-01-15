#pragma once

#include <vulkan/vulkan.h>

namespace vk{class Structure;}
namespace vk::structure{class Viewport;}


namespace vk::presentation{

class Viewport
{
public:
  Viewport(vk::Structure* vk_struct);
  ~Viewport();

public:
  //Main function
  void init();
  void update_viewport();

  //Subfunction
  vk::structure::Viewport* create_viewport();

private:
  vk::Structure* vk_struct;
};

}
