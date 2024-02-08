#pragma once

#include <Utility/Specific/common.h>

namespace vk::render{class Node;}
namespace utl::element{class Window;}


namespace vk::render{

class SCE : public utl::shader::Base
{
public:
  SCE(vk::render::Node* node_render);
  ~SCE();

  //Main function
  void init_shader();

private:
  utl::element::Window* utl_window;
};

}
