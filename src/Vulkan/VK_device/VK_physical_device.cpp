#include "VK_physical_device.h"
#include "../VK_window/VK_surface.h"
#include "../VK_engine.h"
#include "../VK_struct/struct_vulkan.h"


//Constructor / Destructor
VK_physical_device::VK_physical_device(VK_engine* vk_engine){
  //---------------------------

  this->struct_vulkan = vk_engine->get_struct_vulkan();
  this->window = vk_engine->get_window();

  struct_vulkan->device.extension.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
  struct_vulkan->device.extension.push_back(VK_KHR_PUSH_DESCRIPTOR_EXTENSION_NAME);

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

  struct_vulkan->device.physical_device = VK_NULL_HANDLE;

  //Find how many GPU are available
  uint32_t nb_device = 0;
  vkEnumeratePhysicalDevices(struct_vulkan->instance.instance, &nb_device, nullptr);
  if(nb_device == 0){
    throw std::runtime_error("[error] failed to find GPUs with Vulkan support!");
  }

  //List all available GPU and take suitable one
  std::vector<VkPhysicalDevice> vec_physical_device(nb_device);
  vkEnumeratePhysicalDevices(struct_vulkan->instance.instance, &nb_device, vec_physical_device.data());

  // Use an ordered map to automatically sort candidates by increasing score
  std::multimap<int, VkPhysicalDevice> candidates;
  for(VkPhysicalDevice& device : vec_physical_device){
    int score = rate_device_suitability(device);
    candidates.insert(std::make_pair(score, device));
  }

  //Select adequat GPU physical device
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

  //Store device names
  for(VkPhysicalDevice device : vec_physical_device){
    VkPhysicalDeviceProperties deviceProperties;
    vkGetPhysicalDeviceProperties(device, &deviceProperties);
    vec_device_name.push_back(deviceProperties.deviceName);
  }

  //---------------------------
}
void VK_physical_device::compute_extent(){
  //Resolution of the swap chain image
  //---------------------------

  VkSurfaceCapabilitiesKHR capabilities = find_surface_capability(struct_vulkan->device.physical_device);

  if(capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()){
    struct_vulkan->window.extent = capabilities.currentExtent;
  }else{
    glm::vec2 fbo_dim = window->get_window_dim();

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
  struct_vulkan->device.model = property.deviceName;

  //---------------------------
}

//Subfunctions
bool VK_physical_device::is_device_suitable(VkPhysicalDevice physical_device){
  //---------------------------

  //Queue suitable
  int family_graphics = find_queue_family_graphics(physical_device);
  int family_presentation = find_queue_family_presentation(physical_device);
  if(family_graphics == -1 || family_presentation == -1){
    return false;
  }

  //Extension suitable
  bool extension_ok = check_extension_support(physical_device);
  if(extension_ok == false){
    return false;
  }

  //Swap chain suitable
  vector<VkSurfaceFormatKHR> surface_format = find_surface_format(physical_device);
  vector<VkPresentModeKHR> presentation_mode = find_presentation_mode(physical_device);
  bool swapChain_ok = !surface_format.empty() && !presentation_mode.empty();
  if(swapChain_ok == false){
    return false;
  }

  //Supported features
  VkPhysicalDeviceFeatures supportedFeatures;
  vkGetPhysicalDeviceFeatures(physical_device, &supportedFeatures);
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
  std::set<std::string> requiredExtensions(struct_vulkan->device.extension.begin(), struct_vulkan->device.extension.end());
  for(const auto& extension : vec_extension){
    requiredExtensions.erase(extension.extensionName);
  }

  //---------------------------
  return requiredExtensions.empty();
}

//Specific info retrieval
int VK_physical_device::find_queue_family_graphics(VkPhysicalDevice physical_device){
  //---------------------------

  //Get queue family number
  uint32_t nb_queue_family = 0;
  vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &nb_queue_family, nullptr);
  if(nb_queue_family == 0) {
    throw std::runtime_error("[error] No queue families on selected GPU");
  }
  this->nb_queue_graphics = nb_queue_family;

  //List queue families
  std::vector<VkQueueFamilyProperties> vec_queueFamily(nb_queue_family);
  vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &nb_queue_family, vec_queueFamily.data());

  //Search for specific properties (e.g, graphics)
  int i = 0;
  for(const auto& queueFamily : vec_queueFamily){
    //Querying for graphics family
    if(queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT){
      return i;
    }
    i++;
  }

  //---------------------------
  return -1;
}
int VK_physical_device::find_queue_family_presentation(VkPhysicalDevice physical_device){
  //---------------------------

  //Get queue family number
  uint32_t nb_queue_family = 0;
  vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &nb_queue_family, nullptr);
  if(nb_queue_family == 0) {
    throw std::runtime_error("[error] No queue families on selected GPU");
  }
  this->nb_queue_graphics = nb_queue_family;

  //List queue families
  std::vector<VkQueueFamilyProperties> vec_queueFamily(nb_queue_family);
  vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &nb_queue_family, vec_queueFamily.data());

  //Search for specific properties (e.g, graphics)
  int i = 0;
  for(const auto& queueFamily : vec_queueFamily) {
    //Querying for presentation family
    VkBool32 presentSupport = false;
    vkGetPhysicalDeviceSurfaceSupportKHR(physical_device, i, struct_vulkan->window.surface, &presentSupport);
    if(presentSupport){
      return i;
    }
    i++;
  }

  //---------------------------
  return -1;
}
int VK_physical_device::rate_device_suitability(VkPhysicalDevice physical_device){
  int score = 0;
  //---------------------------

  VkPhysicalDeviceProperties deviceProperties;
  vkGetPhysicalDeviceProperties(physical_device, &deviceProperties);

  // Get rid of llvmpipe
  if(deviceProperties.vendorID == 65541){
    return 0;
  }

  // Check if integrated GPU
  if(deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU){
    score += 100000;
  }

  // Check if physical device is suitable
  if(is_device_suitable(physical_device) == false){
    return 0;
  }

  // Maximum possible size of textures affects graphics quality
  score += deviceProperties.limits.maxImageDimension2D;

  //---------------------------
  return score;
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
