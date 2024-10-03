#pragma once

namespace vk{class Structure;}
namespace vk::structure{class Physical;}
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
  void rate_device_suitability(vk::structure::Physical& dev_physical);
  bool device_suitability_onscreen(vk::structure::Physical& dev_physical);
  bool device_suitability_offscreen(vk::structure::Physical& dev_physical);

  //Specific properties
  void find_all_physical_device();
  void find_best_physical_device();
  void find_physical_device_limits(vk::structure::Physical& dev_physical);
  void find_physical_device_properties(vk::structure::Physical& dev_physical);
  void find_physical_device_features(vk::structure::Physical& dev_physical);
  void find_physical_device_support(vk::structure::Physical& dev_physical);
  void find_surface_capability(vk::structure::Physical& dev_physical);
  void find_surface_format(vk::structure::Physical& dev_physical);
  void find_presentation_mode(vk::structure::Physical& dev_physical);
  void find_max_usable_sample_count(vk::structure::Physical& dev_physical);

private:
  vk::Structure* vk_struct;
  vk::device::queue::Manager* vk_queue;
};

}
