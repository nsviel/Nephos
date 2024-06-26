#pragma once

#include <Vulkan/VK_binding/Structure/Descriptor.h>
#include <Vulkan/VK_binding/Structure/Sampler.h>
#include <Vulkan/VK_binding/Structure/Uniform.h>
#include <Vulkan/VK_binding/Structure/Push_constant.h>
#include <vector>


namespace vk::binding::structure{

struct Binding{
  //---------------------------

  //Binding description
  std::vector<vk::structure::Descriptor_required> vec_required_binding;
  vk::structure::Descriptor descriptor;

  //Binding elements
  std::vector<vk::binding::structure::Push_constant*> vec_pushcst;
  std::vector<vk::binding::structure::Uniform*> vec_uniform;
  std::vector<vk::binding::structure::Sampler*> vec_sampler;

  //---------------------------
};

}
