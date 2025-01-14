#pragma once

#include <vulkan/vulkan.h>
#include <string>

namespace vk::structure{class Descriptor;}


namespace vk::gfx::edl{

//Uniform
vk::structure::Descriptor uniform_edl();

//Sampler
vk::structure::Descriptor sampler_color();
vk::structure::Descriptor sampler_depth();

}
