#pragma once

#include <vulkan/vulkan.h>
#include <string>

namespace vk::descriptor::structure{class Descriptor;}


namespace vk::pipeline::topology{

//Uniform
vk::descriptor::structure::Descriptor uniform_mvp();
vk::descriptor::structure::Descriptor uniform_mvp_str();
vk::descriptor::structure::Descriptor uniform_point_size();

}
