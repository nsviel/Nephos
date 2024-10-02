#pragma once

#include <Vulkan/Core/VK_texture/Structure/Texture.h>
#include <Vulkan/Core/VK_data/Structure/Object.h>
#include <unordered_map>
#include <memory>
#include <list>


namespace vk::data::structure{

struct Data{
  //One structure containing all engined inserted data (vk::object)
  //---------------------------

  std::shared_ptr<vk::structure::Object> canvas = std::make_shared<vk::structure::Object>();
  std::unordered_map< int, std::shared_ptr<vk::structure::Object> > map_object;
  std::list<std::shared_ptr<vk::structure::Texture>> list_vk_texture;

  //---------------------------
};

}
