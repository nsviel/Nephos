#pragma once

#include <vulkan/vulkan.h>
#include <string>

namespace vk::descriptor::structure{class Descriptor;}


namespace vk::postprocess{

//Uniform
vk::descriptor::structure::Descriptor uniform_edl();

//Sampler
vk::descriptor::structure::Descriptor sampler_color();
vk::descriptor::structure::Descriptor sampler_depth();

}
