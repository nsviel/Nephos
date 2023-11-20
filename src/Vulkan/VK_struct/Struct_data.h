#ifndef STRUCT_DATA_H
#define STRUCT_DATA_H

#include <VK_struct/Struct_vk_entity.h>
#include <VK_struct/Struct_image.h>

#include <UTL_specific/common.h>


struct Struct_data{
  //---------------------------

  Struct_vk_entity canvas;
  std::vector<Struct_image*> vec_texture;
  std::list<Struct_vk_entity*> list_object;

  //---------------------------
};


#endif
