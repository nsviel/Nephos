#pragma once

#include <Vulkan/VK_struct/Namespace.h>
#include <Utility/Specific/common.h>


namespace vk::structure{

struct Data{
  //---------------------------

  vk::structure::Entity canvas;
  std::vector<Image*> vec_texture;
  std::list<vk::structure::Entity*> list_object;

  //---------------------------
};

}
