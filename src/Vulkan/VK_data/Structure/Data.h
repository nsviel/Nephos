#pragma once

#include <Vulkan/VK_image/Structure/Texture.h>
#include <Vulkan/VK_struct/Struct_object.h>
#include <list>


namespace vk::data::structure{

struct Data{
  //One structure containing all engined inserted data (vk::object)
  //---------------------------

  vk::structure::Object canvas;
  std::list<vk::structure::Texture*> list_vk_texture;
  std::list<vk::structure::Object*> list_vk_object;

  //---------------------------
};

}
