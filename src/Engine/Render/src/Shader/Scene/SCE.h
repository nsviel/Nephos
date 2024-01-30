#pragma once

#include <Utility/Specific/common.h>

namespace eng::render{class Node;}
namespace utl::element{class Window;}


namespace eng::shader{

class SCE : public utl::shader::Base
{
public:
  SCE(eng::render::Node* node_render);
  ~SCE();

  //Main function
  void init_shader();

private:
  utl::element::Window* utl_window;
};

}
