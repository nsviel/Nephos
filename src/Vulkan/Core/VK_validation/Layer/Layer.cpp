#include "Layer.h"

#include <Vulkan/Namespace.h>


namespace vk::validation{

//Constructor / Destructor
Layer::Layer(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_messenger = new vk::validation::Messenger(vk_struct);

  //---------------------------
}
Layer::~Layer(){}

//Main function
void Layer::init_validation_layer(){
  if(!vk_struct->core.validation.enable) return;
  //---------------------------

  this->create_layer_info();
  if(!check_validation_support()) return;
  this->create_feature_info();
  vk_messenger->create_messenger_info();

  //---------------------------
}

//Subfunction
void Layer::create_layer_info(){
  //---------------------------

  //Layer info
  std::vector<const char*>& vec_layer = vk_struct->core.validation.vec_layer;
  vec_layer.clear();
  vec_layer.push_back("VK_LAYER_KHRONOS_validation");

  //Feature enable
  std::vector<VkValidationFeatureEnableEXT>& vec_feature_enable = vk_struct->core.validation.vec_feature_enable;
  vec_feature_enable.clear();
  //vec_feature_enable.push_back(VK_VALIDATION_FEATURE_ENABLE_BEST_PRACTICES_EXT);
  vec_feature_enable.push_back(VK_VALIDATION_FEATURE_ENABLE_DEBUG_PRINTF_EXT);

  //Feature disable
  std::vector<VkValidationFeatureDisableEXT>& vec_feature_disable = vk_struct->core.validation.vec_feature_disable;
  vec_feature_disable.clear();
  vec_feature_disable.push_back(VK_VALIDATION_FEATURE_DISABLE_SHADER_VALIDATION_CACHE_EXT);

  //---------------------------
}
void Layer::create_feature_info(){
  //---------------------------

  VkValidationFeaturesEXT feature_info = {};
  feature_info.sType = VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT;
  feature_info.enabledValidationFeatureCount = static_cast<uint32_t>(vk_struct->core.validation.vec_feature_enable.size());
  feature_info.pEnabledValidationFeatures = vk_struct->core.validation.vec_feature_enable.data();
  feature_info.disabledValidationFeatureCount = static_cast<uint32_t>(vk_struct->core.validation.vec_feature_disable.size());
  feature_info.pDisabledValidationFeatures = vk_struct->core.validation.vec_feature_disable.data();
  feature_info.pNext = &vk_struct->core.validation.messenger_info;

  //---------------------------
  vk_struct->core.validation.feature_info = feature_info;
}
bool Layer::check_validation_support(){
  //---------------------------

  //Get layer count
  uint32_t layer_count;
  vkEnumerateInstanceLayerProperties(&layer_count, nullptr);

  //Get layer property
  std::vector<VkLayerProperties> layer_available(layer_count);
  vkEnumerateInstanceLayerProperties(&layer_count, layer_available.data());

  //Check if requested layer is available
  for(const char* layer_name : vk_struct->core.validation.vec_layer){
    bool layer_found = false;

    for(const auto& layer_properties : layer_available){
      if(strcmp(layer_name, layer_properties.layerName) == 0){
        layer_found = true;
        break;
      }
    }

    if(!layer_found){
      return false;
    }
  }

  //---------------------------
  return true;
}

}
