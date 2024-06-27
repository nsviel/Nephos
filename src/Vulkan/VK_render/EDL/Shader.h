#pragma once

#include <Utility/Base/Shader/Base.h>

namespace vk{class Structure;}
namespace vk::render::edl{class Structure;}


namespace vk::render::edl{

class Shader : public utl::shader::Base
{
public:
  //Contrustor / destructor
  Shader(vk::Structure* vk_struct);
  ~Shader();

  //Main function
  void init_shader();
  void update_shader();

  inline vk::render::edl::Structure* get_edl_struct(){return edl_struct;}

private:
  vk::Structure* vk_struct;
  vk::render::edl::Structure* edl_struct;
};

}
