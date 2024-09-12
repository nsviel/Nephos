#pragma once

#include <Utility/Base/Shader/Base.h>

namespace vk{class Structure;}
namespace vk::render::structure{class EDL;}


namespace vk::render::edl{

class Shader : public utl::shader::Base
{
public:
  //Contrustor / destructor
  Shader(vk::Structure* vk_struct);
  ~Shader();

public:
  //Main function
  void update_shader();

  inline vk::render::structure::EDL* get_edl_struct(){return edl_struct;}

private:
  vk::Structure* vk_struct;
  vk::render::structure::EDL* edl_struct;
};

}
