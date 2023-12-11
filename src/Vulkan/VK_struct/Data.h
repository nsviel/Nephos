#pragma once

#include <VK_struct/Namespace.h>
#include <VK_struct/Image.h>
#include <VK_struct/Entity.h>
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
