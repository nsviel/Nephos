#pragma once

#include <VK_struct/Namespace.h>
#include <UTL_specific/common.h>




class VK_physical_device
{
public:
  //Constructor / Destructor
  VK_physical_device(vk::structure::Struct_vulkan* struct_vulkan);
  ~VK_physical_device();

public:
  //Main functions
  void init();
  void compute_extent();

  //Device selection
  void rate_device_suitability(vk::structure::Physical_device& struct_device);
  bool device_suitability_onscreen(vk::structure::Physical_device& struct_device);
  bool device_suitability_offscreen(vk::structure::Physical_device& struct_device);

  //Specific properties
  void find_physical_devices();
  void find_physical_device_best();
  void find_physical_device_properties(vk::structure::Physical_device& struct_device);
  void find_physical_device_features(vk::structure::Physical_device& struct_device);
  void find_physical_device_support(vk::structure::Physical_device& struct_device);
  void find_surface_capability(vk::structure::Physical_device& struct_device);
  void find_surface_format(vk::structure::Physical_device& struct_device);
  void find_presentation_mode(vk::structure::Physical_device& struct_device);
  void find_queue_nb_family(vk::structure::Physical_device& struct_device);
  void find_queue_graphics_idx(vk::structure::Physical_device& struct_device);
  void find_queue_presentation_idx(vk::structure::Physical_device& struct_device);

private:
  vk::structure::Struct_vulkan* struct_vulkan;
};
