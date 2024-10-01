#pragma once

#include <vulkan/vulkan.h>
#include <string>

namespace vk::structure{class Descriptor;}


namespace vk::compute::dtc{

//Sampler
vk::structure::Descriptor storage_depth();
vk::structure::Descriptor storage_tablexy();
vk::structure::Descriptor storage_cloud();

}
