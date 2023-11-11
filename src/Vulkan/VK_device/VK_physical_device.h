#ifndef VK_PHYSICAL_DEVICE_H
#define VK_PHYSICAL_DEVICE_H

#include <VK_struct/Struct_physical_device.h>
#include <ELE_specific/common.h>

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
  void rate_device_suitability(Struct_physical_device& struct_device);
  bool device_suitability(Struct_physical_device& struct_device);
  bool device_suitability_headless(Struct_physical_device& struct_device);

  //Specific properties
  void find_physical_devices();
  void find_physical_device_best();
  void find_physical_device_properties(Struct_physical_device& struct_device);
  void find_physical_device_features(Struct_physical_device& struct_device);
  void find_physical_device_support(Struct_physical_device& struct_device);
  void find_surface_capability(Struct_physical_device& struct_device);
  void find_surface_format(Struct_physical_device& struct_device);
  void find_presentation_mode(Struct_physical_device& struct_device);
  void find_queue_nb_family(Struct_physical_device& struct_device);
  void find_queue_graphics_idx(Struct_physical_device& struct_device);
  void find_queue_presentation_idx(Struct_physical_device& struct_device);

private:
  Struct_vulkan* struct_vulkan;
};

#endif
