#pragma once

#include <vulkan/vulkan.h>
#include <string>

namespace vk::structure{class Descriptor;}


namespace vk::geometry{

//Uniform
vk::structure::Descriptor uniform_mvp();
vk::structure::Descriptor uniform_point_size();
vk::structure::Descriptor uniform_has_texture();
vk::structure::Descriptor sampler_texture();

//Storage
vk::structure::Descriptor storage_cloud();

}
