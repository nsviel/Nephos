#pragma once

#include <Vulkan/Core/VK_pool/Structure/Descriptor_set.h>
#include <Vulkan/Core/VK_binding/Structure/Descriptor_set.h>
#include <Vulkan/Core/VK_binding/Structure/Layout.h>


namespace vk::pipeline::structure{

struct Descriptor{
  //---------------------------

  vk::pool::structure::Descriptor_set pool;
  vk::structure::Layout layout;

  //---------------------------
};

}
