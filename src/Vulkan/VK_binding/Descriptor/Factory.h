#pragma once

#include <vulkan/vulkan.h>
#include <string>

namespace vk::binding::structure{class Descriptor;}


namespace vk::binding{

//Sampler
vk::binding::structure::Descriptor sampler_color();
vk::binding::structure::Descriptor sampler_depth();

//Uniform
vk::binding::structure::Descriptor uniform_mvp();
vk::binding::structure::Descriptor uniform_point_size();
vk::binding::structure::Descriptor uniform_edl();

}
