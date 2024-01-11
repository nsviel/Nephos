#pragma once

#include <Vulkan/VK_struct/Namespace.h>
#include <Utility/Specific/common.h>


namespace vk::structure{

struct Data{
  //One structure containing all engined inserted data (vk::object)
  //---------------------------

  vk::structure::Object canvas;
  std::vector<Image*> vec_texture;
  std::list<vk::structure::Object*> list_object;

  //---------------------------
};

}
