#pragma once

#include <vulkan/vulkan.h>
#include <string>

namespace vk::descriptor::structure{class Descriptor;}


namespace vk::geometry{

//Uniform
vk::descriptor::structure::Descriptor uniform_mvp();
vk::descriptor::structure::Descriptor uniform_point_size();
vk::descriptor::structure::Descriptor uniform_dynamic();

//Sampler
vk::descriptor::structure::Descriptor sampler_color();
vk::descriptor::structure::Descriptor sampler_depth();

}
