#pragma once

#include <vulkan/vulkan.h>
#include <string>

namespace vk::descriptor::structure{class Descriptor;}


namespace vk::pipeline::edl{

//Uniform
vk::descriptor::structure::Descriptor uniform_mvp();
vk::descriptor::structure::Descriptor uniform_point_size();
vk::descriptor::structure::Descriptor uniform_edl();

//Sampler
vk::descriptor::structure::Descriptor sampler_color();
vk::descriptor::structure::Descriptor sampler_depth();

}
