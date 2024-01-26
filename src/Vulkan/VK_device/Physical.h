#pragma once

#include <Utility/Specific/common.h>

namespace vk::structure{class Vulkan;}
namespace vk::structure{class Physical_device;}


namespace vk::device{

class Physical
{
public:
  //Constructor / Destructor
  Physical(vk::structure::Vulkan* struct_vulkan);
  ~Physical();

public:
  //Main functions
  void init();
  void compute_extent();

  //Device selection
  void rate_device_suitability(vk::structure::Physical_device& dev_physical);
  bool device_suitability_onscreen(vk::structure::Physical_device& dev_physical);
  bool device_suitability_offscreen(vk::structure::Physical_device& dev_physical);

  //Specific properties
  void find_physical_devices();
  void find_physical_device_best();
  void find_physical_device_properties(vk::structure::Physical_device& dev_physical);
  void find_physical_device_features(vk::structure::Physical_device& dev_physical);
  void find_physical_device_support(vk::structure::Physical_device& dev_physical);
  void find_surface_capability(vk::structure::Physical_device& dev_physical);
  void find_surface_format(vk::structure::Physical_device& dev_physical);
  void find_presentation_mode(vk::structure::Physical_device& dev_physical);
  void find_queue_nb_family(vk::structure::Physical_device& dev_physical);
  void find_queue_graphics_idx(vk::structure::Physical_device& dev_physical);
  void find_queue_presentation_idx(vk::structure::Physical_device& dev_physical);
  void find_max_usable_sample_count(vk::structure::Physical_device& dev_physical);

private:
  vk::structure::Vulkan* struct_vulkan;
};

}
