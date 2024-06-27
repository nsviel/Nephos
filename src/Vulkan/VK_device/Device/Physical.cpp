#include "Physical.h"

#include <Vulkan/Namespace.h>


namespace vk::device{

//Constructor / Destructor
Physical::Physical(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_dev_queue = new vk::device::Queue(vk_struct);

  //---------------------------
}
Physical::~Physical(){}

//Main function
void Physical::find_physical_device(){
  //---------------------------

  this->find_all_physical_device();
  this->find_best_physical_device();
  this->compute_extent();

  //---------------------------
}
void Physical::compute_extent(){
  //---------------------------

  if(vk_struct->param.headless){
    vk_struct->window.extent.width = vk_struct->param.headless_dim.x;
    vk_struct->window.extent.height = vk_struct->param.headless_dim.y;
  }
  else{
    this->find_surface_capability(vk_struct->device.physical_device);
    VkSurfaceCapabilitiesKHR capabilities = vk_struct->device.physical_device.capabilities;

    if(capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()){
      vk_struct->window.extent = capabilities.currentExtent;
    }
    else{
      glm::vec2 fbo_dim = vk_struct->window.dimension;
      vk_struct->window.extent = {
        static_cast<uint32_t>(fbo_dim.x),
        static_cast<uint32_t>(fbo_dim.y)
      };

      vk_struct->window.extent.width = std::clamp(vk_struct->window.extent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
      vk_struct->window.extent.height = std::clamp(vk_struct->window.extent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);
    }
  }

  //---------------------------
}

//Device selection
void Physical::find_all_physical_device(){
  //---------------------------

  //Find how many GPU are available
  uint32_t nb_device = 0;
  vkEnumeratePhysicalDevices(vk_struct->instance.handle, &nb_device, nullptr);
  if(nb_device == 0){
    throw std::runtime_error("[error] failed to find GPUs with Vulkan support!");
  }

  //List all available GPU and take suitable one
  std::vector<VkPhysicalDevice> vec_physical_device(nb_device);
  vkEnumeratePhysicalDevices(vk_struct->instance.handle, &nb_device, vec_physical_device.data());

  //Store physical device properties
  for(VkPhysicalDevice device : vec_physical_device){
    vk::device::structure::Physical physical_device;
    physical_device.handle = device;
    this->find_physical_device_properties(physical_device);
    this->find_physical_device_limits(physical_device);
    vk_struct->instance.vec_physical_device.push_back(physical_device);
  }

  //---------------------------
}
void Physical::find_best_physical_device(){
  //---------------------------

  // Use an ordered map to automatically sort candidates by increasing score
  std::multimap<int, vk::device::structure::Physical> candidates;
  for(int i=0; i<vk_struct->instance.vec_physical_device.size(); i++){
    vk::device::structure::Physical& physical_device = vk_struct->instance.vec_physical_device[i];
    this->rate_device_suitability(physical_device);
    candidates.insert(std::make_pair(physical_device.selection_score, physical_device));
  }

  //Select adequat GPU physical device
  vk_struct->device.physical_device.handle = VK_NULL_HANDLE;
  if(candidates.rbegin()->first > 0){
    vk_struct->device.physical_device = candidates.rbegin()->second;
  }else{
    std::cout<<"[error] failed to find a suitable GPU"<<endl;
    std::cout<<"-------------------------------------"<<endl;
    std::cout<<"Detected physical devices:"<<endl;
    for(auto it = candidates.begin(); it != candidates.end(); ++it){
      int score = it->first;
      const vk::device::structure::Physical& device = it->second;
      std::cout<<"-> Physical_device: "<<device.name<< " << score "<<score<<std::endl;
    }
    exit(0);
  }
  if(vk_struct->device.physical_device.handle == VK_NULL_HANDLE){
    throw std::runtime_error("[error] problem retrieving a suitable GPU");
  }

  //---------------------------
}
void Physical::rate_device_suitability(vk::device::structure::Physical& physical_device){
  int score = 0;
  //---------------------------

  //If llvmpipe, set score to the minimum
  if(physical_device.vendor_ID == 65541){
    physical_device.selection_score = 0;
    return;
  }

  // Check if physical device is suitable
  bool device_suitable;
  if(vk_struct->param.headless){
    device_suitable = device_suitability_offscreen(physical_device);
  }else{
    device_suitable = device_suitability_onscreen(physical_device);
  }
  if(device_suitable == false){
    physical_device.selection_score = 0;
    return;
  }

  // Check if integrated GPU
  if(physical_device.type == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU){
    physical_device.discrete_gpu = true;
    if(vk_struct->param.dedicated_gpu){
      score += 100000;
    }
    else{
      score -= 100000;
    }
  }

  // Maximum possible size of textures affects graphics quality
  score += physical_device.max_image_dim;

  //---------------------------
  physical_device.selection_score = score;
}
bool Physical::device_suitability_onscreen(vk::device::structure::Physical& physical_device){
  //---------------------------

  //Queue suitability
  vk_dev_queue->find_queue_family_composition(physical_device);
  bool queue_ok = vk_dev_queue->suitability_for_presentation(physical_device);
  if(queue_ok == false) return false;

  //Extension suitable
  this->find_physical_device_support(physical_device);
  if(physical_device.has_extension_support == false) return false;

  //Swap chain suitable
  this->find_surface_capability(physical_device);
  this->find_surface_format(physical_device);
  this->find_presentation_mode(physical_device);
  bool swapChain_ok = !physical_device.formats.empty() && !physical_device.presentation_mode.empty();
  if(swapChain_ok == false) return false;

  //Supported features
  this->find_physical_device_features(physical_device);
  this->find_max_usable_sample_count(physical_device);
  bool msaa_ok = physical_device.features.samplerAnisotropy;
  bool line_ok = physical_device.features.wideLines;
  bool geom_ok = physical_device.features.geometryShader;
  if(msaa_ok == false || line_ok == false || geom_ok == false){
    return false;
  }

  //---------------------------
  return true;
}
bool Physical::device_suitability_offscreen(vk::device::structure::Physical& physical_device){
  //---------------------------

  //Queue suitable
  vk_dev_queue->find_queue_family_composition(physical_device);
  bool queue_ok = vk_dev_queue->suitability_for_graphics(physical_device);
  if(queue_ok == false) return false;

  //Extension suitable
  this->find_physical_device_support(physical_device);
  if(physical_device.has_extension_support == false){
    return false;
  }

  //Supported features
  this->find_physical_device_features(physical_device);
  this->find_max_usable_sample_count(physical_device);
  bool msaa_ok = physical_device.features.samplerAnisotropy;
  bool line_ok = physical_device.features.wideLines;
  bool geom_ok = physical_device.features.geometryShader;
  if(msaa_ok == false || line_ok == false || geom_ok == false){
    return false;
  }

  //---------------------------
  return true;
}

//Specific properties
void Physical::find_physical_device_limits(vk::device::structure::Physical& physical_device){
  //---------------------------

  VkPhysicalDeviceProperties device_properties;
  vkGetPhysicalDeviceProperties(physical_device.handle, &device_properties);
  VkPhysicalDeviceLimits device_limits = device_properties.limits;

  if(device_limits.timestampPeriod == 0){
    //throw std::runtime_error{"The selected device does not support timestamp queries!"};
  }

  if(!device_limits.timestampComputeAndGraphics){
  	/*// Check if the graphics queue used in this sample supports time stamps
  	VkQueueFamilyProperties graphics_queue_family_properties = device->get_suitable_graphics_queue().get_properties();
  	if(graphics_queue_family_properties.timestampValidBits == 0){
  		throw std::runtime_error{"The selected graphics queue family does not support timestamp queries!"};
  	}*/
  }

  physical_device.timestamp_period = device_limits.timestampPeriod;

  //---------------------------
}
void Physical::find_physical_device_properties(vk::device::structure::Physical& physical_device){
  //---------------------------

  VkPhysicalDeviceProperties properties;
  vkGetPhysicalDeviceProperties(physical_device.handle, &properties);
  physical_device.properties = properties;
  physical_device.name = properties.deviceName;
  physical_device.vendor_ID = properties.vendorID;
  physical_device.type = properties.deviceType;
  physical_device.max_image_dim = properties.limits.maxImageDimension2D;

  //---------------------------
}
void Physical::find_physical_device_features(vk::device::structure::Physical& physical_device){
  //---------------------------

  VkPhysicalDeviceFeatures supportedFeatures;
  vkGetPhysicalDeviceFeatures(physical_device.handle, &supportedFeatures);

  //---------------------------
  physical_device.features = supportedFeatures;
}
void Physical::find_physical_device_support(vk::device::structure::Physical& physical_device){
  //---------------------------

  //Get physical_device extension number
  uint32_t num_ext;
  vkEnumerateDeviceExtensionProperties(physical_device.handle, nullptr, &num_ext, nullptr);

  //List physical_device extension
  std::vector<VkExtensionProperties> vec_ext_capable(num_ext);
  vkEnumerateDeviceExtensionProperties(physical_device.handle, nullptr, &num_ext, vec_ext_capable.data());

  //Check if all required extension are in the list
  std::vector<const char*> vec_ext_required = vk_struct->instance.extension_device;
  std::set<std::string> set_ext_required(vec_ext_required.begin(), vec_ext_required.end());
  for(const auto& extension : vec_ext_capable){
    set_ext_required.erase(extension.extensionName);
  }

  //---------------------------
  physical_device.has_extension_support = set_ext_required.empty();
}
void Physical::find_surface_capability(vk::device::structure::Physical& physical_device){
  //---------------------------

  //Get basic surface capabilities
  VkSurfaceCapabilitiesKHR capabilities;
  vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physical_device.handle, vk_struct->window.surface, &capabilities);

  //---------------------------
  physical_device.capabilities = capabilities;
}
void Physical::find_surface_format(vk::device::structure::Physical& physical_device){
  //---------------------------

  //Get supported surface format number
  uint32_t nb_format;
  vkGetPhysicalDeviceSurfaceFormatsKHR(physical_device.handle, vk_struct->window.surface, &nb_format, nullptr);
  if(nb_format == 0){
    std::cout<<"[error] No physical device surface format"<<endl;
  }

  //Get supported surface format list
  std::vector<VkSurfaceFormatKHR> formats(nb_format);
  vkGetPhysicalDeviceSurfaceFormatsKHR(physical_device.handle, vk_struct->window.surface, &nb_format, formats.data());

  //---------------------------
  physical_device.formats = formats;
}
void Physical::find_presentation_mode(vk::device::structure::Physical& physical_device){
  //---------------------------

  //Get presentation mode number
  uint32_t nb_mode_presentation;
  vkGetPhysicalDeviceSurfacePresentModesKHR(physical_device.handle, vk_struct->window.surface, &nb_mode_presentation, nullptr);
  if(nb_mode_presentation == 0){
    std::cout<<"[error] No physical device surface presentation mode"<<endl;
  }

  //Get presentation mode list
  std::vector<VkPresentModeKHR> presentation_mode(nb_mode_presentation);
  vkGetPhysicalDeviceSurfacePresentModesKHR(physical_device.handle, vk_struct->window.surface, &nb_mode_presentation, presentation_mode.data());

  //---------------------------
  physical_device.presentation_mode = presentation_mode;
}
void Physical::find_max_usable_sample_count(vk::device::structure::Physical& physical_device){
  VkSampleCountFlagBits max_sample;
  //---------------------------

  VkSampleCountFlags counts = physical_device.properties.limits.framebufferColorSampleCounts & physical_device.properties.limits.framebufferDepthSampleCounts;
  if(counts & VK_SAMPLE_COUNT_64_BIT){ max_sample = VK_SAMPLE_COUNT_64_BIT; }
  else if(counts & VK_SAMPLE_COUNT_32_BIT){ max_sample = VK_SAMPLE_COUNT_32_BIT; }
  else if(counts & VK_SAMPLE_COUNT_16_BIT){ max_sample = VK_SAMPLE_COUNT_16_BIT; }
  else if(counts & VK_SAMPLE_COUNT_8_BIT){ max_sample = VK_SAMPLE_COUNT_8_BIT; }
  else if(counts & VK_SAMPLE_COUNT_4_BIT){ max_sample = VK_SAMPLE_COUNT_4_BIT; }
  else if(counts & VK_SAMPLE_COUNT_2_BIT){ max_sample = VK_SAMPLE_COUNT_2_BIT; }
  else max_sample = VK_SAMPLE_COUNT_1_BIT;

  max_sample = VK_SAMPLE_COUNT_1_BIT; // for now

  //---------------------------
  physical_device.max_sample_count = max_sample;
}

}
