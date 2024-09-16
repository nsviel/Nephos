#pragma once

#include <Vulkan/Core/VK_binding/Structure/Descriptor_set.h>
#include <Vulkan/Core/VK_binding/Structure/Layout.h>


namespace vk::binding::structure{

struct Binding{
  //---------------------------

  vk::binding::structure::Descriptor_set descriptor_set;
  vk::binding::structure::Layout layout;

  //---------------------------
};

}
