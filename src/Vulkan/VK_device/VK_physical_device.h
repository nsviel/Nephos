#ifndef VK_PHYSICAL_DEVICE_H
#define VK_PHYSICAL_DEVICE_H

#include <ELE_specific/common.h>

class VK_engine;
class Struct_vulkan;


class VK_physical_device
{
public:
  //Constructor / Destructor
  VK_physical_device(Struct_vulkan* struct_vulkan);
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
  int find_queue_nb_family(VkPhysicalDevice physical_device);
  int find_queue_graphics_idx(VkPhysicalDevice physical_device);
  int find_queue_presentation_idx(VkPhysicalDevice physical_device);
  int rate_device_suitability(VkPhysicalDevice device);

  //Find specific properties
  VkSurfaceCapabilitiesKHR find_surface_capability(VkPhysicalDevice physical_device);
  vector<VkSurfaceFormatKHR> find_surface_format(VkPhysicalDevice physical_device);
  vector<VkPresentModeKHR> find_presentation_mode(VkPhysicalDevice physical_device);
  VkPhysicalDeviceProperties find_device_property(VkPhysicalDevice physical_device);

private:
  Struct_vulkan* struct_vulkan;
};

#endif
