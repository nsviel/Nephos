#pragma once

#include <VK_struct/Namespace.h>
#include <UTL_specific/common.h>

class Struct_vulkan;


class VK_physical_device
{
public:
  //Constructor / Destructor
  VK_physical_device(Struct_vulkan* struct_vulkan);
  ~VK_physical_device();

public:
  //Main functions
  void init();
  void compute_extent();

  //Device selection
  void rate_device_suitability(vk::structure::Struct_vk_physical_device& struct_device);
  bool device_suitability_onscreen(vk::structure::Struct_vk_physical_device& struct_device);
  bool device_suitability_offscreen(vk::structure::Struct_vk_physical_device& struct_device);

  //Specific properties
  void find_physical_devices();
  void find_physical_device_best();
  void find_physical_device_properties(vk::structure::Struct_vk_physical_device& struct_device);
  void find_physical_device_features(vk::structure::Struct_vk_physical_device& struct_device);
  void find_physical_device_support(vk::structure::Struct_vk_physical_device& struct_device);
  void find_surface_capability(vk::structure::Struct_vk_physical_device& struct_device);
  void find_surface_format(vk::structure::Struct_vk_physical_device& struct_device);
  void find_presentation_mode(vk::structure::Struct_vk_physical_device& struct_device);
  void find_queue_nb_family(vk::structure::Struct_vk_physical_device& struct_device);
  void find_queue_graphics_idx(vk::structure::Struct_vk_physical_device& struct_device);
  void find_queue_presentation_idx(vk::structure::Struct_vk_physical_device& struct_device);

private:
  Struct_vulkan* struct_vulkan;
};
