#include "Layer.h"

#include <Vulkan/Namespace.h>


namespace vk::validation{

//Constructor / Destructor
Layer::Layer(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;

  //---------------------------
}
Layer::~Layer(){}

//Main function
void Layer::init_validation_info(){
  if(!vk_struct->core.validation.enable) return;
  //---------------------------

  this->create_layer_info();
  if(!check_validation_support()) return;
  this->create_messenger_info();
  this->create_feature_info();

  //---------------------------
}
void Layer::create_validation_messenger(){
  if(!vk_struct->core.validation.enable) return;
  //---------------------------

  VkDebugUtilsMessengerCreateInfoEXT messenger_info{};
  messenger_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
  messenger_info.messageSeverity =
    VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | \
    VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | \
    VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT | \
    VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT;
  messenger_info.messageType =
    VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | \
    VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | \
    VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
  messenger_info.pfnUserCallback = vk::validation::Callback;
  messenger_info.pNext = nullptr;

  auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(vk_struct->core.instance.handle, "vkCreateDebugUtilsMessengerEXT");
  if(func == nullptr) return;

  VkResult result = func(vk_struct->core.instance.handle, &messenger_info, nullptr, &vk_struct->core.validation.messenger);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to set up debug messenger!");
  }

  //---------------------------
}
void Layer::clean_validation_messenger(){
  if(!vk_struct->core.validation.enable) return;
  //---------------------------

  auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(vk_struct->core.instance.handle, "vkDestroyDebugUtilsMessengerEXT");
  if(func == nullptr) return;

  func(vk_struct->core.instance.handle, vk_struct->core.validation.messenger, nullptr);

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
void Layer::create_messenger_info(){
  //---------------------------

  VkDebugUtilsMessengerCreateInfoEXT messenger_info{};
  messenger_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
  messenger_info.messageSeverity =
    VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | \
    VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | \
    VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
  messenger_info.messageType =
    VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | \
    VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | \
    VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
  messenger_info.pfnUserCallback = vk::validation::Callback;
  messenger_info.pNext = nullptr;

  //---------------------------
  vk_struct->core.validation.messenger_info = messenger_info;
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
