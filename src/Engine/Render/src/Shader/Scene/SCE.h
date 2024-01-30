#pragma once

#include <Utility/Base/Shader/Shader.h>
#include <Utility/Specific/common.h>

namespace eng::render{class Node;}
namespace utl::element{class Window;}


namespace eng::shader{

class SCE : public utl::base::Shader
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
