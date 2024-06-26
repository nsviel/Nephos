#pragma once

#include <Utility/Base/Shader/Base.h>

namespace vk::structure{class Vulkan;}


namespace vk::render::scene{

class Shader : public utl::shader::Base
{
public:
  Shader(vk::structure::Vulkan* vk_struct);
  ~Shader();

  //Main function
  void init_shader();

private:
  vk::structure::Vulkan* vk_struct;
};

}
