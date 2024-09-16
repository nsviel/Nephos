#pragma once

#include <Vulkan/Core/VK_image/Structure/Texture.h>
#include <Vulkan/Core/VK_data/Structure/Object.h>
#include <memory>
#include <list>


namespace vk::data::structure{

struct Data{
  //One structure containing all engined inserted data (vk::object)
  //---------------------------

  std::shared_ptr<vk::structure::Object> canvas = std::make_shared<vk::structure::Object>();
  std::list< std::shared_ptr<vk::structure::Texture> > list_vk_texture;
  std::list< std::shared_ptr<vk::structure::Object> > list_vk_object;

  //---------------------------
};

}
