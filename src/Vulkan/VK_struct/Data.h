#pragma once

#include <Vulkan/VK_struct/Namespace.h>
#include <Vulkan/VK_struct/Image.h>
#include <Vulkan/VK_struct/Entity.h>
#include <Utility/UTL_specific/common.h>


namespace vk::structure{

struct Data{
  //---------------------------

  vk::structure::Entity canvas;
  std::vector<Image*> vec_texture;
  std::list<vk::structure::Entity*> list_object;

  //---------------------------
};

}
