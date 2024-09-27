#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <string>

namespace vk{class Structure;}


namespace vk::validation{

class Layer
{
public:
  //Constructor / Destructor
  Layer(vk::Structure* vk_struct);
  ~Layer();

public:
  //Main function
  void init_validation_info();
  void create_validation_messenger();
  void clean_validation_messenger();

  //Subfunction
  void create_layer_info();
  void create_messenger_info();
  void create_feature_info();
  bool check_validation_support();

private:
  vk::Structure* vk_struct;
};

}
