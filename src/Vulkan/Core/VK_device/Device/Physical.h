#pragma once

namespace vk{class Structure;}
namespace vk::device::structure{class Physical;}
namespace vk::device::queue{class Manager;}


namespace vk::device{

class Physical
{
public:
  //Constructor / Destructor
  Physical(vk::Structure* vk_struct);
  ~Physical();

public:
  //Main function
  void find_physical_device();
  void compute_extent();

  //Device selection
  void rate_device_suitability(vk::device::structure::Physical& dev_physical);
  bool device_suitability_onscreen(vk::device::structure::Physical& dev_physical);
  bool device_suitability_offscreen(vk::device::structure::Physical& dev_physical);

  //Specific properties
  void find_all_physical_device();
  void find_best_physical_device();
  void find_physical_device_limits(vk::device::structure::Physical& dev_physical);
  void find_physical_device_properties(vk::device::structure::Physical& dev_physical);
  void find_physical_device_features(vk::device::structure::Physical& dev_physical);
  void find_physical_device_support(vk::device::structure::Physical& dev_physical);
  void find_surface_capability(vk::device::structure::Physical& dev_physical);
  void find_surface_format(vk::device::structure::Physical& dev_physical);
  void find_presentation_mode(vk::device::structure::Physical& dev_physical);
  void find_max_usable_sample_count(vk::device::structure::Physical& dev_physical);

private:
  vk::Structure* vk_struct;
  vk::device::queue::Manager* vk_queue;
};

}
