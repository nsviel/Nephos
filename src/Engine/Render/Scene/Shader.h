#pragma once

#include <Utility/Specific/Common.h>

namespace eng::render{class Manager;}
namespace utl::element{class Window;}


namespace rnd::scene{

class Shader : public utl::shader::Base
{
public:
  Shader(eng::render::Manager* node_render);
  ~Shader();

  //Main function
  void init_shader();

private:
  utl::element::Window* utl_window;
};

}
