#pragma once

#include <Utility/Specific/Common.h>

namespace vk::validation{class Layer;}
namespace vk::structure{class Vulkan;}


namespace vk::instance{

class Instance
{
public:
  //Constructor / Destructor
  Instance(vk::structure::Vulkan* vk_struct);
  ~Instance();

public:
  //Main functions
  void init();
  void clean();

  //Subfunction
  void create_instance();

private:
  vk::validation::Layer* vk_validation;
  vk::structure::Vulkan* vk_struct;
};

}
