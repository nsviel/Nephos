#pragma once

#include <Utility/Base/Shader/Base.h>

namespace vk{class Structure;}


namespace vk::render::scene{

class Shader : public utl::shader::Base
{
public:
  Shader(vk::Structure* vk_struct);
  ~Shader();

  //Main function
  void init_shader();

  //Subfunction
  void init_shader_line();
  void init_shader_point();
  void init_shader_triangle();

private:
  vk::Structure* vk_struct;
};

}
