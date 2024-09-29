#pragma once

#include <vulkan/vulkan.h>
#include <string>

namespace vk::structure{class Descriptor;}


namespace vk::compute::dtc{

//Sampler
vk::structure::Descriptor sampler_depth();
vk::structure::Descriptor sampler_table_xy();
vk::structure::Descriptor sampler_storage_pc();

}
