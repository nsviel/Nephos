#pragma once

#include <VK_struct/Namespace.h>
#include <VK_struct/Struct_vk_image.h>
#include <VK_struct/Struct_vk_entity.h>
#include <UTL_specific/common.h>


namespace vk::structure{

struct Struct_vk_data{
  //---------------------------

  vk::structure::Struct_vk_entity canvas;
  std::vector<Struct_vk_image*> vec_texture;
  std::list<vk::structure::Struct_vk_entity*> list_object;

  //---------------------------
};

}
