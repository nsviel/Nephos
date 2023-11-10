#include "VK_physical_device.h"

#include <VK_presentation/VK_surface.h>
#include <VK_main/VK_engine.h>
#include <VK_main/Struct_vulkan.h>


//Constructor / Destructor
VK_physical_device::VK_physical_device(Struct_vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;

  struct_vulkan->instance.extension_khr.clear();
  struct_vulkan->instance.extension_khr.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
  struct_vulkan->instance.extension_khr.push_back(VK_KHR_PUSH_DESCRIPTOR_EXTENSION_NAME);

  //---------------------------
}
VK_physical_device::~VK_physical_device(){}

//Main functions
void VK_physical_device::init_physical_device(){
  //---------------------------

  this->select_physical_device();
  this->compute_extent();
  this->retrieve_device_name();

  //---------------------------
}
void VK_physical_device::select_physical_device(){
  //---------------------------

  this->find_physical_devices();
  this->find_physical_device_best();

  //---------------------------
}
void VK_physical_device::compute_extent(){
  //Resolution of the swap chain image
  //---------------------------

  VkSurfaceCapabilitiesKHR capabilities = find_surface_capability(struct_vulkan->device.physical_device);

  if(capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()){
    struct_vulkan->window.extent = capabilities.currentExtent;
  }else{
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
void VK_physical_device::retrieve_device_name(){
  //---------------------------

  VkPhysicalDeviceProperties property = find_device_property(struct_vulkan->device.physical_device);
  struct_vulkan->info.gpu_name = property.deviceName;

  //---------------------------
}

//Subfunctions
bool VK_physical_device::is_device_suitable(Struct_physical_device& struct_device){
  //---------------------------

  //Queue suitable
  this->find_queue_nb_family(struct_device);
  this->find_queue_graphics_idx(struct_device);
  this->find_queue_presentation_idx(struct_device);
  if(struct_vulkan->device.queue_graphics_idx == -1 || struct_vulkan->device.queue_presentation_idx == -1){
    return false;
  }

  //Extension suitable
  bool extension_ok = check_extension_support(struct_device.physical_device);
  if(extension_ok == false){
    return false;
  }

  //Swap chain suitable
  vector<VkSurfaceFormatKHR> surface_format = find_surface_format(struct_device.physical_device);
  vector<VkPresentModeKHR> presentation_mode = find_presentation_mode(struct_device.physical_device);
  bool swapChain_ok = !surface_format.empty() && !presentation_mode.empty();
  if(swapChain_ok == false){
    return false;
  }

  //Supported features
  VkPhysicalDeviceFeatures supportedFeatures;
  vkGetPhysicalDeviceFeatures(struct_device.physical_device, &supportedFeatures);
  bool msaa_ok = supportedFeatures.samplerAnisotropy;
  bool line_ok = supportedFeatures.wideLines;
  bool geom_ok = supportedFeatures.geometryShader;
  if(msaa_ok == false || line_ok == false || geom_ok == false){
    return false;
  }

  //---------------------------
  return true;
}
bool VK_physical_device::check_extension_support(VkPhysicalDevice physical_device){
  //---------------------------

  //Get physical_device extension number
  uint32_t nb_extension;
  vkEnumerateDeviceExtensionProperties(physical_device, nullptr, &nb_extension, nullptr);

  //List physical_device extension
  std::vector<VkExtensionProperties> vec_extension(nb_extension);
  vkEnumerateDeviceExtensionProperties(physical_device, nullptr, &nb_extension, vec_extension.data());

  //Check if all required extension are in the list
  std::set<std::string> requiredExtensions(struct_vulkan->instance.extension_khr.begin(), struct_vulkan->instance.extension_khr.end());
  for(const auto& extension : vec_extension){
    requiredExtensions.erase(extension.extensionName);
  }

  //---------------------------
  return requiredExtensions.empty();
}

//Specific info retrieval
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
    VkPhysicalDeviceProperties deviceProperties;
    vkGetPhysicalDeviceProperties(device, &deviceProperties);

    Struct_physical_device struct_device;
    struct_device.name = deviceProperties.deviceName;
    struct_device.physical_device = device;
    struct_vulkan->instance.vec_physical_device.push_back(struct_device);
  }

  //---------------------------
}
void VK_physical_device::find_physical_device_best(){
  //---------------------------

  // Use an ordered map to automatically sort candidates by increasing score
  std::multimap<int, VkPhysicalDevice> candidates;
  for(int i=0; i<struct_vulkan->instance.vec_physical_device.size(); i++){
    Struct_physical_device& struct_device = struct_vulkan->instance.vec_physical_device[i];

    this->rate_device_suitability(struct_device);
    candidates.insert(std::make_pair(struct_device.selection_score, struct_device.physical_device));
  }

  //Select adequat GPU physical device
  struct_vulkan->device.physical_device = VK_NULL_HANDLE;
  if(candidates.rbegin()->first > 0){
    struct_vulkan->device.physical_device = candidates.rbegin()->second;

    VkPhysicalDeviceProperties deviceProperties;
    vkGetPhysicalDeviceProperties(struct_vulkan->device.physical_device, &deviceProperties);
    //say(deviceProperties.deviceName);

  }else {
    throw std::runtime_error("failed to find a suitable GPU!");
  }
  if(struct_vulkan->device.physical_device == VK_NULL_HANDLE){
    throw std::runtime_error("[error] failed to find a suitable GPU!");
  }

  //---------------------------
}
void VK_physical_device::find_queue_nb_family(Struct_physical_device& struct_device){
  //---------------------------

  uint32_t nb_queue_family = 0;
  vkGetPhysicalDeviceQueueFamilyProperties(struct_device.physical_device, &nb_queue_family, nullptr);
  if(nb_queue_family == 0) {
    throw std::runtime_error("[error] No queue families on selected GPU");
  }

  //---------------------------
  struct_vulkan->device.nb_queue_family = nb_queue_family;
}
void VK_physical_device::find_queue_graphics_idx(Struct_physical_device& struct_device){
  //---------------------------

  //List queue families
  std::vector<VkQueueFamilyProperties> vec_queueFamily(struct_vulkan->device.nb_queue_family );
  vkGetPhysicalDeviceQueueFamilyProperties(struct_device.physical_device, &struct_vulkan->device.nb_queue_family , vec_queueFamily.data());

  //Search for specific properties (e.g, graphics)
  int i = 0;
  for(const auto& queueFamily : vec_queueFamily){
    //Querying for graphics family
    if(queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT){
      struct_vulkan->device.queue_graphics_idx = i;
      return;
    }
    i++;
  }

  //---------------------------
  struct_vulkan->device.queue_graphics_idx = -1;
}
void VK_physical_device::find_queue_presentation_idx(Struct_physical_device& struct_device){
  //---------------------------

  //List queue families
  std::vector<VkQueueFamilyProperties> vec_queueFamily(struct_vulkan->device.nb_queue_family );
  vkGetPhysicalDeviceQueueFamilyProperties(struct_device.physical_device, &struct_vulkan->device.nb_queue_family , vec_queueFamily.data());

  //Search for specific properties (e.g, graphics)
  int i = 0;
  for(const auto& queueFamily : vec_queueFamily) {
    //Querying for presentation family
    VkBool32 presentSupport = false;
    vkGetPhysicalDeviceSurfaceSupportKHR(struct_device.physical_device, i, struct_vulkan->window.surface, &presentSupport);
    if(presentSupport){
      struct_vulkan->device.queue_presentation_idx = i;
      return;
    }
    i++;
  }

  //---------------------------
  struct_vulkan->device.queue_presentation_idx = -1;
}
void VK_physical_device::rate_device_suitability(Struct_physical_device& struct_device){
  int score = 0;
  //---------------------------

  VkPhysicalDeviceProperties deviceProperties;
  vkGetPhysicalDeviceProperties(struct_device.physical_device, &deviceProperties);

  // Get rid of llvmpipe
  if(deviceProperties.vendorID == 65541){
    struct_device.selection_score = 0;
    return;
  }

  // Check if physical device is suitable
  if(is_device_suitable(struct_device) == false){
    struct_device.selection_score = 0;
    return;
  }

  // Check if integrated GPU
  if(deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU){
    score += 100000;
  }

  // Maximum possible size of textures affects graphics quality
  score += deviceProperties.limits.maxImageDimension2D;

  //---------------------------
  struct_device.selection_score = score;
}

//Find specific properties
VkSurfaceCapabilitiesKHR VK_physical_device::find_surface_capability(VkPhysicalDevice physical_device){
  //---------------------------

  //Get basic surface capabilities
  VkSurfaceCapabilitiesKHR capabilities;
  vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physical_device, struct_vulkan->window.surface, &capabilities);

  //---------------------------
  return capabilities;
}
vector<VkSurfaceFormatKHR> VK_physical_device::find_surface_format(VkPhysicalDevice physical_device){
  vector<VkSurfaceFormatKHR> formats;
  //---------------------------

  //Get supported surface format number
  uint32_t nb_format;
  vkGetPhysicalDeviceSurfaceFormatsKHR(physical_device, struct_vulkan->window.surface, &nb_format, nullptr);

  //Get supported surface format list
  if(nb_format != 0){
    formats.resize(nb_format);
    vkGetPhysicalDeviceSurfaceFormatsKHR(physical_device, struct_vulkan->window.surface, &nb_format, formats.data());
  }

  //---------------------------
  return formats;
}
vector<VkPresentModeKHR> VK_physical_device::find_presentation_mode(VkPhysicalDevice physical_device){
  vector<VkPresentModeKHR> presentation_mode;
  //---------------------------

  //Get presentation mode number
  uint32_t nb_mode_presentation;
  vkGetPhysicalDeviceSurfacePresentModesKHR(physical_device, struct_vulkan->window.surface, &nb_mode_presentation, nullptr);

  //Get presentation mode list
  if(nb_mode_presentation != 0){
    presentation_mode.resize(nb_mode_presentation);
    vkGetPhysicalDeviceSurfacePresentModesKHR(physical_device, struct_vulkan->window.surface, &nb_mode_presentation, presentation_mode.data());
  }

  //---------------------------
  return presentation_mode;
}
VkPhysicalDeviceProperties VK_physical_device::find_device_property(VkPhysicalDevice physical_device){
  //---------------------------

  VkPhysicalDeviceProperties property{};
  vkGetPhysicalDeviceProperties(struct_vulkan->device.physical_device, &property);

  //---------------------------
  return property;
}
