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

  auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(vk_struct->core.instance.handle, "vkCreateDebugUtilsMessengerEXT");
  if(func == nullptr) return;

  VkResult result = func(vk_struct->core.instance.handle, &vk_struct->core.validation.messenger_info, nullptr, &vk_struct->core.validation.messenger);
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

  //Feature info
  std::vector<VkValidationFeatureEnableEXT>& vec_feature = vk_struct->core.validation.vec_feature;
  vec_feature.clear();
  //vec_feature.push_back(VK_VALIDATION_FEATURE_ENABLE_BEST_PRACTICES_EXT);
  vec_feature.push_back(VK_VALIDATION_FEATURE_ENABLE_DEBUG_PRINTF_EXT);

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
  feature_info.enabledValidationFeatureCount = static_cast<uint32_t>(vk_struct->core.validation.vec_feature.size());
  feature_info.pEnabledValidationFeatures = vk_struct->core.validation.vec_feature.data();
  feature_info.pNext = &vk_struct->core.validation.messenger_info;

  //---------------------------
  vk_struct->core.validation.feature_info = feature_info;
}
bool Layer::check_validation_support(){
  //---------------------------

  //Checks if all of the requested layers are available
  uint32_t layerCount;
  vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

  std::vector<VkLayerProperties> availableLayers(layerCount);
  vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

  //Check if all of the layers in validation_layers exist in the availableLayers list
  for(const char* layerName : vk_struct->core.validation.vec_layer){
    bool layerFound = false;

    for(const auto& layerProperties : availableLayers){
      if(strcmp(layerName, layerProperties.layerName) == 0){
        layerFound = true;
        break;
      }
    }

    if(!layerFound){
      return false;
    }
  }

  //---------------------------
  return true;
}

}
