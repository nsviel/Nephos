#pragma once

#include <Utility/Base/Shader/Base.h>

namespace vk{class Structure;}


namespace vk::render::scene{

class Shader : public utl::shader::Base
{
public:
  Shader(vk::Structure* vk_struct);
  ~Shader();

public:
  //Main function
  void build_shader_info();

  //Subfunction
  void init_shader_line();
  void init_shader_point();
  void init_shader_triangle();

private:
  vk::Structure* vk_struct;
};

}
