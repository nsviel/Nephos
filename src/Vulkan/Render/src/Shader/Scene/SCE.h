#pragma once

#include <Utility/Specific/common.h>

namespace vk{class Node;}


namespace vk::render{

class SCE : public utl::shader::Base
{
public:
  SCE(vk::Node* node_render);
  ~SCE();

  //Main function
  void init_shader();

private:
};

}
