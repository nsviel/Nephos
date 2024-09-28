#pragma once

#include <Vulkan/Core/VK_binding/Structure/Descriptor_set.h>
#include <Vulkan/Core/VK_binding/Structure/Layout.h>


namespace vk::pipeline::structure{

struct Descriptor{
  //---------------------------

  vk::structure::Descriptor_set descriptor_set;
  vk::structure::Layout layout;

  //---------------------------
};

}
