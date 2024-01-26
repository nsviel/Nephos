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
    vk::structure::Physical_device dev_physical;
    dev_physical.physical_device = device;
    this->find_physical_device_properties(dev_physical);
    struct_vulkan->instance.vec_physical_device.push_back(dev_physical);
  }

  //---------------------------
}
void Physical::find_physical_device_best(){
  //---------------------------

  // Use an ordered map to automatically sort candidates by increasing score
  std::multimap<int, vk::structure::Physical_device> candidates;
  for(int i=0; i<struct_vulkan->instance.vec_physical_device.size(); i++){
    vk::structure::Physical_device& dev_physical = struct_vulkan->instance.vec_physical_device[i];
    this->rate_device_suitability(dev_physical);
    candidates.insert(std::make_pair(dev_physical.selection_score, dev_physical));
  }

  //Select adequat GPU physical device
  struct_vulkan->device.physical_device.physical_device = VK_NULL_HANDLE;
  if(candidates.rbegin()->first > 0){
    struct_vulkan->device.physical_device = candidates.rbegin()->second;
  }else {
    throw std::runtime_error("failed to find a suitable GPU!");
  }
  if(struct_vulkan->device.physical_device.physical_device == VK_NULL_HANDLE){
    throw std::runtime_error("[error] failed to find a suitable GPU!");
  }

  //---------------------------
}
void Physical::rate_device_suitability(vk::structure::Physical_device& dev_physical){
  int score = 0;
  //---------------------------

  // Get rid of llvmpipe
  if(dev_physical.vendorID == 65541){
    dev_physical.selection_score = 0;
    return;
  }

  // Check if physical device is suitable
  bool device_suitable;
  if(struct_vulkan->param.headless){
    device_suitable = device_suitability_offscreen(dev_physical);
  }else{
    device_suitable = device_suitability_onscreen(dev_physical);
  }
  if(device_suitable == false){
    dev_physical.selection_score = 0;
    return;
  }

  // Check if integrated GPU
  if(dev_physical.type == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU){
    if(struct_vulkan->param.dedicated_gpu){
      score += 100000;
    }
    else{
      score -= 100000;
    }
  }

  // Maximum possible size of textures affects graphics quality
  score += dev_physical.max_image_dim;

  //---------------------------
  dev_physical.selection_score = score;
}
bool Physical::device_suitability_onscreen(vk::structure::Physical_device& dev_physical){
  //---------------------------

  //Queue suitable
  this->find_queue_nb_family(dev_physical);
  this->find_queue_graphics_idx(dev_physical);
  this->find_queue_presentation_idx(dev_physical);
  if(dev_physical.queue_graphics_idx == -1){
    return false;
  }
  if(dev_physical.queue_presentation_idx == -1 && struct_vulkan->param.headless == false){
    return false;
  }

  //Extension suitable
  this->find_physical_device_support(dev_physical);
  if(dev_physical.has_extension_support == false){
    return false;
  }

  //Swap chain suitable
  this->find_surface_capability(dev_physical);
  this->find_surface_format(dev_physical);
  this->find_presentation_mode(dev_physical);
  bool swapChain_ok = !dev_physical.formats.empty() && !dev_physical.presentation_mode.empty();
  if(swapChain_ok == false){
    return false;
  }

  //Supported features
  this->find_physical_device_features(dev_physical);
  this->find_max_usable_sample_count(dev_physical);
  bool msaa_ok = dev_physical.features.samplerAnisotropy;
  bool line_ok = dev_physical.features.wideLines;
  bool geom_ok = dev_physical.features.geometryShader;
  if(msaa_ok == false || line_ok == false || geom_ok == false){
    return false;
  }

  //---------------------------
  return true;
}
bool Physical::device_suitability_offscreen(vk::structure::Physical_device& dev_physical){
  //---------------------------

  //Queue suitable
  this->find_queue_nb_family(dev_physical);
  this->find_queue_graphics_idx(dev_physical);
  if(dev_physical.queue_graphics_idx == -1){
    return false;
  }

  //Extension suitable
  this->find_physical_device_support(dev_physical);
  if(dev_physical.has_extension_support == false){
    return false;
  }

  //Supported features
  this->find_physical_device_features(dev_physical);
  bool msaa_ok = dev_physical.features.samplerAnisotropy;
  bool line_ok = dev_physical.features.wideLines;
  bool geom_ok = dev_physical.features.geometryShader;
  if(msaa_ok == false || line_ok == false || geom_ok == false){
    return false;
  }

  //---------------------------
  return true;
}

//Specific properties
void Physical::find_physical_device_properties(vk::structure::Physical_device& dev_physical){
  //---------------------------

  VkPhysicalDeviceProperties properties;
  vkGetPhysicalDeviceProperties(dev_physical.physical_device, &properties);
  dev_physical.properties = properties;
  dev_physical.name = properties.deviceName;
  dev_physical.vendorID = properties.vendorID;
  dev_physical.type = properties.deviceType;
  dev_physical.max_image_dim = properties.limits.maxImageDimension2D;

  //---------------------------
}
void Physical::find_physical_device_features(vk::structure::Physical_device& dev_physical){
  //---------------------------

  VkPhysicalDeviceFeatures supportedFeatures;
  vkGetPhysicalDeviceFeatures(dev_physical.physical_device, &supportedFeatures);

  //---------------------------
  dev_physical.features = supportedFeatures;
}
void Physical::find_physical_device_support(vk::structure::Physical_device& dev_physical){
  //---------------------------

  //Get physical_device extension number
  uint32_t nb_extension;
  vkEnumerateDeviceExtensionProperties(dev_physical.physical_device, nullptr, &nb_extension, nullptr);

  //List physical_device extension
  std::vector<VkExtensionProperties> vec_extension(nb_extension);
  vkEnumerateDeviceExtensionProperties(dev_physical.physical_device, nullptr, &nb_extension, vec_extension.data());

  //Check if all required extension are in the list
  std::set<std::string> requiredExtensions(struct_vulkan->instance.extension_device.begin(), struct_vulkan->instance.extension_device.end());
  for(const auto& extension : vec_extension){
    requiredExtensions.erase(extension.extensionName);
  }

  //---------------------------
  dev_physical.has_extension_support = requiredExtensions.empty();
}
void Physical::find_surface_capability(vk::structure::Physical_device& dev_physical){
  //---------------------------

  //Get basic surface capabilities
  VkSurfaceCapabilitiesKHR capabilities;
  vkGetPhysicalDeviceSurfaceCapabilitiesKHR(dev_physical.physical_device, struct_vulkan->window.surface, &capabilities);

  //---------------------------
  dev_physical.capabilities = capabilities;
}
void Physical::find_surface_format(vk::structure::Physical_device& dev_physical){
  //---------------------------

  //Get supported surface format number
  uint32_t nb_format;
  vkGetPhysicalDeviceSurfaceFormatsKHR(dev_physical.physical_device, struct_vulkan->window.surface, &nb_format, nullptr);
  if(nb_format == 0){
    cout<<"[error] No physical device surface format"<<endl;
  }

  //Get supported surface format list
  vector<VkSurfaceFormatKHR> formats(nb_format);
  vkGetPhysicalDeviceSurfaceFormatsKHR(dev_physical.physical_device, struct_vulkan->window.surface, &nb_format, formats.data());

  //---------------------------
  dev_physical.formats = formats;
}
void Physical::find_presentation_mode(vk::structure::Physical_device& dev_physical){
  //---------------------------

  //Get presentation mode number
  uint32_t nb_mode_presentation;
  vkGetPhysicalDeviceSurfacePresentModesKHR(dev_physical.physical_device, struct_vulkan->window.surface, &nb_mode_presentation, nullptr);
  if(nb_mode_presentation == 0){
    cout<<"[error] No physical device surface presentation mode"<<endl;
  }

  //Get presentation mode list
  vector<VkPresentModeKHR> presentation_mode(nb_mode_presentation);
  vkGetPhysicalDeviceSurfacePresentModesKHR(dev_physical.physical_device, struct_vulkan->window.surface, &nb_mode_presentation, presentation_mode.data());

  //---------------------------
  dev_physical.presentation_mode = presentation_mode;
}
void Physical::find_queue_nb_family(vk::structure::Physical_device& dev_physical){
  //---------------------------

  uint32_t nb_queue_family = 0;
  vkGetPhysicalDeviceQueueFamilyProperties(dev_physical.physical_device, &nb_queue_family, nullptr);
  if(nb_queue_family == 0) {
    throw std::runtime_error("[error] No queue families on selected GPU");
  }

  // Retrieve information about each queue family
  vector<VkQueueFamilyProperties> queue_families(nb_queue_family);
  vkGetPhysicalDeviceQueueFamilyProperties(dev_physical.physical_device, &nb_queue_family, queue_families.data());

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
      vkGetPhysicalDeviceSurfaceSupportKHR(dev_physical.physical_device, i, struct_vulkan->window.surface, &presentSupport);
      if(presentSupport){
        nb_queue_presentation += queue_families[i].queueCount;
      }
    }
  }

  dev_physical.nb_queue_family = nb_queue_family;
  dev_physical.nb_queue_graphics = nb_queue_graphics;
  dev_physical.nb_queue_compute = nb_queue_compute;
  dev_physical.nb_queue_transfer = nb_queue_transfer;
  dev_physical.nb_queue_sparseBinding = nb_queue_sparseBinding;
  dev_physical.nb_queue_presentation = nb_queue_presentation;

  //---------------------------
}
void Physical::find_queue_graphics_idx(vk::structure::Physical_device& dev_physical){
  //---------------------------

  //List queue families
  std::vector<VkQueueFamilyProperties> vec_queueFamily(dev_physical.nb_queue_family );
  vkGetPhysicalDeviceQueueFamilyProperties(dev_physical.physical_device, &dev_physical.nb_queue_family , vec_queueFamily.data());

  //Search for specific properties (e.g, graphics)
  int i = 0;
  for(const auto& queueFamily : vec_queueFamily){
    //Querying for graphics family
    if(queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT){
      dev_physical.queue_graphics_idx = i;
      return;
    }
    i++;
  }

  //---------------------------
}
void Physical::find_queue_presentation_idx(vk::structure::Physical_device& dev_physical){
  //---------------------------

  //List queue families
  std::vector<VkQueueFamilyProperties> vec_queueFamily(dev_physical.nb_queue_family );
  vkGetPhysicalDeviceQueueFamilyProperties(dev_physical.physical_device, &dev_physical.nb_queue_family , vec_queueFamily.data());

  //Search for specific properties (e.g, graphics)
  int i = 0;
  for(const auto& queueFamily : vec_queueFamily) {
    //Querying for presentation family
    VkBool32 presentSupport = false;
    vkGetPhysicalDeviceSurfaceSupportKHR(dev_physical.physical_device, i, struct_vulkan->window.surface, &presentSupport);
    if(presentSupport){
      dev_physical.queue_presentation_idx = i;
      return;
    }
    i++;
  }

  //---------------------------
}
void Physical::find_max_usable_sample_count(vk::structure::Physical_device& dev_physical){
  VkSampleCountFlagBits max_sample;
  //---------------------------

  VkSampleCountFlags counts = dev_physical.properties.limits.framebufferColorSampleCounts & dev_physical.properties.limits.framebufferDepthSampleCounts;
  if (counts & VK_SAMPLE_COUNT_64_BIT) { max_sample = VK_SAMPLE_COUNT_64_BIT; }
  else if (counts & VK_SAMPLE_COUNT_32_BIT) { max_sample = VK_SAMPLE_COUNT_32_BIT; }
  else if (counts & VK_SAMPLE_COUNT_16_BIT) { max_sample = VK_SAMPLE_COUNT_16_BIT; }
  else if (counts & VK_SAMPLE_COUNT_8_BIT) { max_sample = VK_SAMPLE_COUNT_8_BIT; }
  else if (counts & VK_SAMPLE_COUNT_4_BIT) { max_sample = VK_SAMPLE_COUNT_4_BIT; }
  else if (counts & VK_SAMPLE_COUNT_2_BIT) { max_sample = VK_SAMPLE_COUNT_2_BIT; }
  else max_sample = VK_SAMPLE_COUNT_1_BIT;

  max_sample = VK_SAMPLE_COUNT_1_BIT; // for now

  //---------------------------
  dev_physical.max_sample_count = max_sample;
}

}
