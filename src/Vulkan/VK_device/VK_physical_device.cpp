#include "VK_physical_device.h"

#include <VK_main/Struct_vulkan.h>


//Constructor / Destructor
VK_physical_device::VK_physical_device(Struct_vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;

  //---------------------------
}
VK_physical_device::~VK_physical_device(){}

//Main functions
void VK_physical_device::init(){
  //---------------------------

  this->find_physical_devices();
  this->find_physical_device_best();
  this->compute_extent();

  //---------------------------
}
void VK_physical_device::compute_extent(){
  //---------------------------

  this->find_surface_capability(struct_vulkan->device.struct_device);

  VkSurfaceCapabilitiesKHR capabilities = struct_vulkan->device.struct_device.capabilities;
  if(struct_vulkan->param.headless){
    struct_vulkan->window.extent.width = 200;
    struct_vulkan->window.extent.height = 200;
  }
  else if(capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()){
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

  //---------------------------
}

//Device selection
void VK_physical_device::find_physical_devices(){
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
    Struct_physical_device struct_device;
    struct_device.physical_device = device;
    this->find_physical_device_properties(struct_device);
    struct_vulkan->instance.vec_physical_device.push_back(struct_device);
  }

  //---------------------------
}
void VK_physical_device::find_physical_device_best(){
  //---------------------------

  // Use an ordered map to automatically sort candidates by increasing score
  std::multimap<int, Struct_physical_device> candidates;
  for(int i=0; i<struct_vulkan->instance.vec_physical_device.size(); i++){
    Struct_physical_device& struct_device = struct_vulkan->instance.vec_physical_device[i];

    this->rate_device_suitability(struct_device);
    candidates.insert(std::make_pair(struct_device.selection_score, struct_device));
  }

  //Select adequat GPU physical device
  struct_vulkan->device.struct_device.physical_device = VK_NULL_HANDLE;
  if(candidates.rbegin()->first > 0){
    struct_vulkan->device.struct_device = candidates.rbegin()->second;
  }else {
    throw std::runtime_error("failed to find a suitable GPU!");
  }
  if(struct_vulkan->device.struct_device.physical_device == VK_NULL_HANDLE){
    throw std::runtime_error("[error] failed to find a suitable GPU!");
  }

  //---------------------------
}
void VK_physical_device::rate_device_suitability(Struct_physical_device& struct_device){
  int score = 0;
  //---------------------------

  // Get rid of llvmpipe
  if(struct_device.vendorID == 65541){
    struct_device.selection_score = 0;
    return;
  }

  // Check if physical device is suitable
  bool device_suitable;
  if(struct_vulkan->param.headless){
    device_suitable = device_suitability_headless(struct_device);
  }else{
    device_suitable = device_suitability(struct_device);
  }
  if(device_suitable == false){
    struct_device.selection_score = 0;
    return;
  }

  // Check if integrated GPU
  if(struct_device.type == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU){
    score += 100000;
  }

  // Maximum possible size of textures affects graphics quality
  score += struct_device.max_image_dim;

  //---------------------------
  struct_device.selection_score = score;
}
bool VK_physical_device::device_suitability(Struct_physical_device& struct_device){
  //---------------------------

  //Queue suitable
  this->find_queue_nb_family(struct_device);
  this->find_queue_graphics_idx(struct_device);
  this->find_queue_presentation_idx(struct_device);
  if(struct_device.queue_graphics_idx == -1){
    return false;
  }
  if(struct_device.queue_presentation_idx == -1 && struct_vulkan->param.headless == false){
    return false;
  }

  //Extension suitable
  this->find_physical_device_support(struct_device);
  if(struct_device.has_extension_support == false){
    return false;
  }

  //Swap chain suitable
  this->find_surface_capability(struct_device);
  this->find_surface_format(struct_device);
  this->find_presentation_mode(struct_device);
  bool swapChain_ok = !struct_device.formats.empty() && !struct_device.presentation_mode.empty();
  if(swapChain_ok == false){
    return false;
  }

  //Supported features
  this->find_physical_device_features(struct_device);
  bool msaa_ok = struct_device.features.samplerAnisotropy;
  bool line_ok = struct_device.features.wideLines;
  bool geom_ok = struct_device.features.geometryShader;
  if(msaa_ok == false || line_ok == false || geom_ok == false){
    return false;
  }

  //---------------------------
  return true;
}
bool VK_physical_device::device_suitability_headless(Struct_physical_device& struct_device){
  //---------------------------

  //Queue suitable
  this->find_queue_nb_family(struct_device);
  this->find_queue_graphics_idx(struct_device);
  if(struct_device.queue_graphics_idx == -1){
    return false;
  }

  //Extension suitable
  this->find_physical_device_support(struct_device);
  if(struct_device.has_extension_support == false){
    return false;
  }

  //Supported features
  this->find_physical_device_features(struct_device);
  bool msaa_ok = struct_device.features.samplerAnisotropy;
  bool line_ok = struct_device.features.wideLines;
  bool geom_ok = struct_device.features.geometryShader;
  if(msaa_ok == false || line_ok == false || geom_ok == false){
    return false;
  }

  //---------------------------
  return true;
}

//Specific properties
void VK_physical_device::find_physical_device_properties(Struct_physical_device& struct_device){
  //---------------------------

  VkPhysicalDeviceProperties properties;
  vkGetPhysicalDeviceProperties(struct_device.physical_device, &properties);
  struct_device.properties = properties;
  struct_device.name = properties.deviceName;
  struct_device.vendorID = properties.vendorID;
  struct_device.type = properties.deviceType;
  struct_device.max_image_dim = properties.limits.maxImageDimension2D;

  //---------------------------
}
void VK_physical_device::find_physical_device_features(Struct_physical_device& struct_device){
  //---------------------------

  VkPhysicalDeviceFeatures supportedFeatures;
  vkGetPhysicalDeviceFeatures(struct_device.physical_device, &supportedFeatures);

  //---------------------------
  struct_device.features = supportedFeatures;
}
void VK_physical_device::find_physical_device_support(Struct_physical_device& struct_device){
  //---------------------------

  //Get physical_device extension number
  uint32_t nb_extension;
  vkEnumerateDeviceExtensionProperties(struct_device.physical_device, nullptr, &nb_extension, nullptr);

  //List physical_device extension
  std::vector<VkExtensionProperties> vec_extension(nb_extension);
  vkEnumerateDeviceExtensionProperties(struct_device.physical_device, nullptr, &nb_extension, vec_extension.data());

  //Check if all required extension are in the list
  std::set<std::string> requiredExtensions(struct_vulkan->instance.extension_khr.begin(), struct_vulkan->instance.extension_khr.end());
  for(const auto& extension : vec_extension){
    requiredExtensions.erase(extension.extensionName);
  }

  //---------------------------
  struct_device.has_extension_support = requiredExtensions.empty();
}
void VK_physical_device::find_surface_capability(Struct_physical_device& struct_device){
  //---------------------------

  //Get basic surface capabilities
  VkSurfaceCapabilitiesKHR capabilities;
  vkGetPhysicalDeviceSurfaceCapabilitiesKHR(struct_device.physical_device, struct_vulkan->window.surface, &capabilities);

  //---------------------------
  struct_device.capabilities = capabilities;
}
void VK_physical_device::find_surface_format(Struct_physical_device& struct_device){
  //---------------------------

  //Get supported surface format number
  uint32_t nb_format;
  vkGetPhysicalDeviceSurfaceFormatsKHR(struct_device.physical_device, struct_vulkan->window.surface, &nb_format, nullptr);
  if(nb_format == 0){
    cout<<"[error] No physical device surface format"<<endl;
  }

  //Get supported surface format list
  vector<VkSurfaceFormatKHR> formats(nb_format);
  vkGetPhysicalDeviceSurfaceFormatsKHR(struct_device.physical_device, struct_vulkan->window.surface, &nb_format, formats.data());

  //---------------------------
  struct_device.formats = formats;
}
void VK_physical_device::find_presentation_mode(Struct_physical_device& struct_device){
  //---------------------------

  //Get presentation mode number
  uint32_t nb_mode_presentation;
  vkGetPhysicalDeviceSurfacePresentModesKHR(struct_device.physical_device, struct_vulkan->window.surface, &nb_mode_presentation, nullptr);
  if(nb_mode_presentation == 0){
    cout<<"[error] No physical device surface presentation mode"<<endl;
  }

  //Get presentation mode list
  vector<VkPresentModeKHR> presentation_mode(nb_mode_presentation);
  vkGetPhysicalDeviceSurfacePresentModesKHR(struct_device.physical_device, struct_vulkan->window.surface, &nb_mode_presentation, presentation_mode.data());

  //---------------------------
  struct_device.presentation_mode = presentation_mode;
}
void VK_physical_device::find_queue_nb_family(Struct_physical_device& struct_device){
  //---------------------------

  uint32_t nb_queue_family = 0;
  vkGetPhysicalDeviceQueueFamilyProperties(struct_device.physical_device, &nb_queue_family, nullptr);
  if(nb_queue_family == 0) {
    throw std::runtime_error("[error] No queue families on selected GPU");
  }

  //---------------------------
  struct_device.nb_queue_family = nb_queue_family;
}
void VK_physical_device::find_queue_graphics_idx(Struct_physical_device& struct_device){
  //---------------------------

  //List queue families
  std::vector<VkQueueFamilyProperties> vec_queueFamily(struct_device.nb_queue_family );
  vkGetPhysicalDeviceQueueFamilyProperties(struct_device.physical_device, &struct_device.nb_queue_family , vec_queueFamily.data());

  //Search for specific properties (e.g, graphics)
  int i = 0;
  for(const auto& queueFamily : vec_queueFamily){
    //Querying for graphics family
    if(queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT){
      struct_device.queue_graphics_idx = i;
      return;
    }
    i++;
  }

  //---------------------------
}
void VK_physical_device::find_queue_presentation_idx(Struct_physical_device& struct_device){
  //---------------------------

  //List queue families
  std::vector<VkQueueFamilyProperties> vec_queueFamily(struct_device.nb_queue_family );
  vkGetPhysicalDeviceQueueFamilyProperties(struct_device.physical_device, &struct_device.nb_queue_family , vec_queueFamily.data());

  //Search for specific properties (e.g, graphics)
  int i = 0;
  for(const auto& queueFamily : vec_queueFamily) {
    //Querying for presentation family
    VkBool32 presentSupport = false;
    vkGetPhysicalDeviceSurfaceSupportKHR(struct_device.physical_device, i, struct_vulkan->window.surface, &presentSupport);
    if(presentSupport){
      struct_device.queue_presentation_idx = i;
      return;
    }
    i++;
  }

  //---------------------------
}
