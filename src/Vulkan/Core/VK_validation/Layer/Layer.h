#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <string>

namespace vk{class Structure;}
namespace vk::validation{class Messenger;}


namespace vk::validation{

class Layer
{
public:
  //Constructor / Destructor
  Layer(vk::Structure* vk_struct);
  ~Layer();

public:
  //Main function
  void init_validation_layer();

  //Subfunction
  void create_layer_info();
  void create_feature_info();
  bool check_validation_support();

private:
  vk::Structure* vk_struct;
  vk::validation::Messenger* vk_messenger;
};

}
