#include "Physical.h"

#include <Vulkan/Namespace.h>


namespace vk::device{

//Constructor / Destructor
Physical::Physical(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;

  //---------------------------
}
Physical::~Physical(){}

//Main functions
void Physical::init(){
  //---------------------------

  this->find_physical_devices();
  this->find_physical_device_best();
  this->compute_extent();

  //---------------------------
}
void Physical::compute_extent(){
  //---------------------------

  if(struct_vulkan->param.headless){
    struct_vulkan->window.extent.width = struct_vulkan->param.headless_dim.x;
    struct_vulkan->window.extent.height = struct_vulkan->param.headless_dim.y;
  }
  else{
    this->find_surface_capability(struct_vulkan->device.physical_device);
    VkSurfaceCapabilitiesKHR capabilities = struct_vulkan->device.physical_device.capabilities;

    if(capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()){
      struct_vulkan->window.extent = capabilities.currentExtent;
    }
    else{
      glm::vec2 fbo_dim = struct_vulkan->window.window_dim;
      struct_vulkan->window.extent = {
        static_cast<uint32_t>(fbo_dim.x),
        static_cast<uint32_t>(fbo_dim.y)
      };

      struct_vulkan->window.extent.width = std::clamp(struct_vulkan->window.extent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
      struct_vulkan->window.extent.height = std::clamp(struct_vulkan->window.extent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);
    }
  }

  //---------------------------
}

//Device selection
void Physical::find_physical_devices(){
  //---------------------------

  //Find how many GPU are available
  uint32_t nb_device = 0;
  vkEnumeratePhysicalDevices(struct_vulkan->instance.instance, &nb_device, nullptr);
  if(nb_device == 0){
    throw std::runtime_error("[error] failed to find GPUs with Vulkan support!");
  }

  //List all available GPU and take suitable one
  vector<VkPhysicalDevice> vec_physical_device(nb_device);
  vkEnumeratePhysicalDevices(struct_vulkan->instance.instance, &nb_device, vec_physical_device.data());

  //Store physical device properties
  for(VkPhysicalDevice device : vec_physical_device){
    vk::structure::Physical_device physical_device;
    physical_device.handle = device;
    this->find_physical_device_properties(physical_device);
    this->find_physical_device_limits(physical_device);
    struct_vulkan->instance.vec_physical_device.push_back(physical_device);
  }

  //---------------------------
}
void Physical::find_physical_device_best(){
  //---------------------------

  // Use an ordered map to automatically sort candidates by increasing score
  std::multimap<int, vk::structure::Physical_device> candidates;
  for(int i=0; i<struct_vulkan->instance.vec_physical_device.size(); i++){
    vk::structure::Physical_device& physical_device = struct_vulkan->instance.vec_physical_device[i];
    this->rate_device_suitability(physical_device);
    candidates.insert(std::make_pair(physical_device.selection_score, physical_device));
  }

  //Select adequat GPU physical device
  struct_vulkan->device.physical_device.handle = VK_NULL_HANDLE;
  if(candidates.rbegin()->first > 0){
    struct_vulkan->device.physical_device = candidates.rbegin()->second;
  }else {
    throw std::runtime_error("failed to find a suitable GPU!");
  }
  if(struct_vulkan->device.physical_device.handle == VK_NULL_HANDLE){
    throw std::runtime_error("[error] failed to find a suitable GPU!");
  }

  //---------------------------
}
void Physical::rate_device_suitability(vk::structure::Physical_device& physical_device){
  int score = 0;
  //---------------------------

  // Get rid of llvmpipe
  if(physical_device.vendorID == 65541){
    physical_device.selection_score = 0;
    return;
  }

  // Check if physical device is suitable
  bool device_suitable;
  if(struct_vulkan->param.headless){
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
    if(struct_vulkan->param.dedicated_gpu){
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
bool Physical::device_suitability_onscreen(vk::structure::Physical_device& physical_device){
  //---------------------------

  //Queue suitable
  this->find_queue_nb_family(physical_device);
  this->find_queue_graphics_idx(physical_device);
  if(physical_device.queue_family_graphics_idx == -1){
    return false;
  }

  this->find_queue_transfer_idx(physical_device);
  if(physical_device.queue_family_transfer_idx == -1){
    return false;
  }

  this->find_queue_presentation_idx(physical_device);
  if(physical_device.queue_family_presentation_idx == -1){
    return false;
  }

  //Extension suitable
  this->find_physical_device_support(physical_device);
  if(physical_device.has_extension_support == false){
    return false;
  }

  //Swap chain suitable
  this->find_surface_capability(physical_device);
  this->find_surface_format(physical_device);
  this->find_presentation_mode(physical_device);
  bool swapChain_ok = !physical_device.formats.empty() && !physical_device.presentation_mode.empty();
  if(swapChain_ok == false){
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
bool Physical::device_suitability_offscreen(vk::structure::Physical_device& physical_device){
  //---------------------------

  //Queue suitable
  this->find_queue_nb_family(physical_device);
  this->find_queue_graphics_idx(physical_device);
  if(physical_device.queue_family_graphics_idx == -1){
    return false;
  }

  //Extension suitable
  this->find_physical_device_support(physical_device);
  if(physical_device.has_extension_support == false){
    return false;
  }

  //Supported features
  this->find_physical_device_features(physical_device);
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
void Physical::find_physical_device_limits(vk::structure::Physical_device& physical_device){
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
  	if (graphics_queue_family_properties.timestampValidBits == 0){
  		throw std::runtime_error{"The selected graphics queue family does not support timestamp queries!"};
  	}*/
  }

  physical_device.timestamp_period = device_limits.timestampPeriod;

  //---------------------------
}
void Physical::find_physical_device_properties(vk::structure::Physical_device& physical_device){
  //---------------------------

  VkPhysicalDeviceProperties properties;
  vkGetPhysicalDeviceProperties(physical_device.handle, &properties);
  physical_device.properties = properties;
  physical_device.name = properties.deviceName;
  physical_device.vendorID = properties.vendorID;
  physical_device.type = properties.deviceType;
  physical_device.max_image_dim = properties.limits.maxImageDimension2D;

  //---------------------------
}
void Physical::find_physical_device_features(vk::structure::Physical_device& physical_device){
  //---------------------------

  VkPhysicalDeviceFeatures supportedFeatures;
  vkGetPhysicalDeviceFeatures(physical_device.handle, &supportedFeatures);

  //---------------------------
  physical_device.features = supportedFeatures;
}
void Physical::find_physical_device_support(vk::structure::Physical_device& physical_device){
  //---------------------------

  //Get physical_device extension number
  uint32_t nb_extension;
  vkEnumerateDeviceExtensionProperties(physical_device.handle, nullptr, &nb_extension, nullptr);

  //List physical_device extension
  std::vector<VkExtensionProperties> vec_extension(nb_extension);
  vkEnumerateDeviceExtensionProperties(physical_device.handle, nullptr, &nb_extension, vec_extension.data());

  //Check if all required extension are in the list
  std::set<std::string> requiredExtensions(struct_vulkan->instance.extension_device.begin(), struct_vulkan->instance.extension_device.end());
  for(const auto& extension : vec_extension){
    requiredExtensions.erase(extension.extensionName);
  }

  //---------------------------
  physical_device.has_extension_support = requiredExtensions.empty();
}
void Physical::find_surface_capability(vk::structure::Physical_device& physical_device){
  //---------------------------

  //Get basic surface capabilities
  VkSurfaceCapabilitiesKHR capabilities;
  vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physical_device.handle, struct_vulkan->window.surface, &capabilities);

  //---------------------------
  physical_device.capabilities = capabilities;
}
void Physical::find_surface_format(vk::structure::Physical_device& physical_device){
  //---------------------------

  //Get supported surface format number
  uint32_t nb_format;
  vkGetPhysicalDeviceSurfaceFormatsKHR(physical_device.handle, struct_vulkan->window.surface, &nb_format, nullptr);
  if(nb_format == 0){
    cout<<"[error] No physical device surface format"<<endl;
  }

  //Get supported surface format list
  vector<VkSurfaceFormatKHR> formats(nb_format);
  vkGetPhysicalDeviceSurfaceFormatsKHR(physical_device.handle, struct_vulkan->window.surface, &nb_format, formats.data());

  //---------------------------
  physical_device.formats = formats;
}
void Physical::find_presentation_mode(vk::structure::Physical_device& physical_device){
  //---------------------------

  //Get presentation mode number
  uint32_t nb_mode_presentation;
  vkGetPhysicalDeviceSurfacePresentModesKHR(physical_device.handle, struct_vulkan->window.surface, &nb_mode_presentation, nullptr);
  if(nb_mode_presentation == 0){
    cout<<"[error] No physical device surface presentation mode"<<endl;
  }

  //Get presentation mode list
  vector<VkPresentModeKHR> presentation_mode(nb_mode_presentation);
  vkGetPhysicalDeviceSurfacePresentModesKHR(physical_device.handle, struct_vulkan->window.surface, &nb_mode_presentation, presentation_mode.data());

  //---------------------------
  physical_device.presentation_mode = presentation_mode;
}
void Physical::find_queue_nb_family(vk::structure::Physical_device& physical_device){
  //---------------------------

  uint32_t nb_queue_family = 0;
  vkGetPhysicalDeviceQueueFamilyProperties(physical_device.handle, &nb_queue_family, nullptr);
  if(nb_queue_family == 0) {
    throw std::runtime_error("[error] No queue families on selected GPU");
  }

  // Retrieve information about each queue family
  vector<VkQueueFamilyProperties> queue_families(nb_queue_family);
  vkGetPhysicalDeviceQueueFamilyProperties(physical_device.handle, &nb_queue_family, queue_families.data());

  // Count the number of each type of queue
  uint32_t nb_queue_graphics = 0;
  uint32_t nb_queue_compute = 0;
  uint32_t nb_queue_transfer = 0;
  uint32_t nb_queue_sparseBinding = 0;
  uint32_t nb_queue_presentation = 0;

  for (uint32_t i = 0; i < nb_queue_family; ++i) {
    nb_queue_graphics += (queue_families[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) ? queue_families[i].queueCount : 0;
    nb_queue_compute += (queue_families[i].queueFlags & VK_QUEUE_COMPUTE_BIT) ? queue_families[i].queueCount : 0;
    nb_queue_transfer += (queue_families[i].queueFlags & VK_QUEUE_TRANSFER_BIT) ? queue_families[i].queueCount : 0;
    nb_queue_sparseBinding += (queue_families[i].queueFlags & VK_QUEUE_SPARSE_BINDING_BIT) ? queue_families[i].queueCount : 0;

    if(struct_vulkan->param.headless == false){
      VkBool32 presentSupport = false;
      vkGetPhysicalDeviceSurfaceSupportKHR(physical_device.handle, i, struct_vulkan->window.surface, &presentSupport);
      if(presentSupport){
        nb_queue_presentation += queue_families[i].queueCount;
      }
    }
  }

  physical_device.nb_queue_family = nb_queue_family;
  physical_device.nb_queue_graphics = nb_queue_graphics;
  physical_device.nb_queue_compute = nb_queue_compute;
  physical_device.nb_queue_transfer = nb_queue_transfer;
  physical_device.nb_queue_sparseBinding = nb_queue_sparseBinding;
  physical_device.nb_queue_presentation = nb_queue_presentation;

  //---------------------------
}
void Physical::find_queue_graphics_idx(vk::structure::Physical_device& physical_device){
  //---------------------------

  //List queue families
  std::vector<VkQueueFamilyProperties> vec_queueFamily(physical_device.nb_queue_family );
  vkGetPhysicalDeviceQueueFamilyProperties(physical_device.handle, &physical_device.nb_queue_family , vec_queueFamily.data());

  //Search for specific properties (e.g, graphics)
  for(int i=0; i<vec_queueFamily.size(); i++){
    const auto& queueFamily = vec_queueFamily[i];

    //Querying for graphics family
    if(queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT){
      physical_device.queue_family_graphics_idx = static_cast<uint32_t>(i);
      return;
    }
  }

  //---------------------------
}
void Physical::find_queue_transfer_idx(vk::structure::Physical_device& physical_device){
  //---------------------------

  // List queue families
  std::vector<VkQueueFamilyProperties> vec_queueFamily(physical_device.nb_queue_family);
  vkGetPhysicalDeviceQueueFamilyProperties(physical_device.handle, &physical_device.nb_queue_family, vec_queueFamily.data());

  // Search for specific properties (e.g., transfer)
  for(int i=0; i<vec_queueFamily.size(); i++){
    const auto& queueFamily = vec_queueFamily[i];

    // Querying for transfer family
    if(queueFamily.queueFlags & VK_QUEUE_TRANSFER_BIT){
      physical_device.queue_family_transfer_idx = static_cast<uint32_t>(i);
      return;
    }
  }

  //---------------------------
}
void Physical::find_queue_presentation_idx(vk::structure::Physical_device& physical_device){
  //---------------------------

  //List queue families
  std::vector<VkQueueFamilyProperties> vec_queueFamily(physical_device.nb_queue_family );
  vkGetPhysicalDeviceQueueFamilyProperties(physical_device.handle, &physical_device.nb_queue_family , vec_queueFamily.data());

  //Search for specific properties (e.g, graphics)
  for(int i=0; i<vec_queueFamily.size(); i++){
    const auto& queueFamily = vec_queueFamily[i];

    //Querying for presentation family
    VkBool32 presentSupport = false;
    vkGetPhysicalDeviceSurfaceSupportKHR(physical_device.handle, static_cast<uint32_t>(i), struct_vulkan->window.surface, &presentSupport);
    if(presentSupport){
      physical_device.queue_family_presentation_idx = static_cast<uint32_t>(i);
      return;
    }
  }

  //---------------------------
}
void Physical::find_max_usable_sample_count(vk::structure::Physical_device& physical_device){
  VkSampleCountFlagBits max_sample;
  //---------------------------

  VkSampleCountFlags counts = physical_device.properties.limits.framebufferColorSampleCounts & physical_device.properties.limits.framebufferDepthSampleCounts;
  if (counts & VK_SAMPLE_COUNT_64_BIT) { max_sample = VK_SAMPLE_COUNT_64_BIT; }
  else if (counts & VK_SAMPLE_COUNT_32_BIT) { max_sample = VK_SAMPLE_COUNT_32_BIT; }
  else if (counts & VK_SAMPLE_COUNT_16_BIT) { max_sample = VK_SAMPLE_COUNT_16_BIT; }
  else if (counts & VK_SAMPLE_COUNT_8_BIT) { max_sample = VK_SAMPLE_COUNT_8_BIT; }
  else if (counts & VK_SAMPLE_COUNT_4_BIT) { max_sample = VK_SAMPLE_COUNT_4_BIT; }
  else if (counts & VK_SAMPLE_COUNT_2_BIT) { max_sample = VK_SAMPLE_COUNT_2_BIT; }
  else max_sample = VK_SAMPLE_COUNT_1_BIT;

  max_sample = VK_SAMPLE_COUNT_1_BIT; // for now

  //---------------------------
  physical_device.max_sample_count = max_sample;
}

}
