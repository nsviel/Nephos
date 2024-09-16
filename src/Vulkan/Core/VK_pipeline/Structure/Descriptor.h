#pragma once

#include <Vulkan/Core/VK_binding/Structure/Descriptor_set.h>
#include <Vulkan/Core/VK_binding/Structure/Layout.h>


namespace vk::pipeline::structure{

struct Descriptor{
  //---------------------------

  vk::descriptor::structure::Descriptor_set descriptor_set;
  vk::descriptor::structure::Layout layout;

  //---------------------------
};

}
