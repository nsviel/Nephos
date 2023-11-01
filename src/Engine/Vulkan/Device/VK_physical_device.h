#ifndef VK_PHYSICAL_DEVICE_H
#define VK_PHYSICAL_DEVICE_H

#include <Specific/common.h>

class VK_engine;
class VK_struct;
class VK_surface;
class VK_instance;


class VK_physical_device
{
public:
  //Constructor / Destructor
  VK_physical_device(VK_engine* vk_engine);
  ~VK_physical_device();

public:
  //Main functions
  void init_physical_device();
  void select_physical_device();
  void compute_extent();
  void retrieve_device_name();

  //Subfunctions
  bool is_device_suitable(VkPhysicalDevice physical_device);
  bool check_extension_support(VkPhysicalDevice physical_device);

  //Specific info retrieval
  int find_queue_family_graphics(VkPhysicalDevice physical_device);
  int find_queue_family_presentation(VkPhysicalDevice physical_device);
  int rate_device_suitability(VkPhysicalDevice device);

  //Find specific properties
  VkSurfaceCapabilitiesKHR find_surface_capability(VkPhysicalDevice physical_device);
  vector<VkSurfaceFormatKHR> find_surface_format(VkPhysicalDevice physical_device);
  vector<VkPresentModeKHR> find_presentation_mode(VkPhysicalDevice physical_device);
  VkPhysicalDeviceProperties find_device_property(VkPhysicalDevice physical_device);

private:
  VK_engine* vk_engine;
  VK_struct* vk_struct;
  VK_surface* vk_surface;
  VK_instance* vk_instance;

  vector<string> vec_device_name;
};

#endif
