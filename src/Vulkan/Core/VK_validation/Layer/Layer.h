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
  void init();
  void create_messenger_info();
  void create_feature_info();
  bool check_validation_support();




  void create_validation_layer();
  void clean_validation_layer();




  //Subfunction

  inline std::vector<const char*> get_validation_layers(){return validation_layers;};

private:
  vk::Structure* vk_struct;

  bool with_validation_layer;
  bool with_best_practice;
  bool with_shader_printf;

  std::vector<const char*> validation_layers;
  std::vector<VkValidationFeatureEnableEXT> EXT_enables;
  VkDebugUtilsMessengerCreateInfoEXT EXT_debug_info;
  VkDebugUtilsMessengerEXT EXT_debug;
  VkValidationFeaturesEXT EXT_feature;
};

}
