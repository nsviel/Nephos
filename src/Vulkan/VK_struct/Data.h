#pragma once

#include <VK_struct/Namespace.h>
#include <VK_struct/Struct_vk_image.h>
#include <VK_struct/Entity.h>
#include <UTL_specific/common.h>


namespace vk::structure{

struct Data{
  //---------------------------

  vk::structure::Entity canvas;
  std::vector<Struct_vk_image*> vec_texture;
  std::list<vk::structure::Entity*> list_object;

  //---------------------------
};

}
