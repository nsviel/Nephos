#pragma once

#include <Utility/Base/Shader/Base.h>

namespace vk::structure{class Vulkan;}
namespace vk::render::edl{class Structure;}


namespace vk::render::edl{

class Shader : public utl::shader::Base
{
public:
  //Contrustor / destructor
  Shader(vk::structure::Vulkan* vk_struct);
  ~Shader();

  //Main function
  void init_shader();
  void update_shader();

  inline vk::render::edl::Structure* get_edl_struct(){return edl_struct;}

private:
  vk::structure::Vulkan* vk_struct;
  vk::render::edl::Structure* edl_struct;
};

}
