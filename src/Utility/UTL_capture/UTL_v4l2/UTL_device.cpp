#include "UTL_device.h"

#include <UTL_file/File.h>


//Constructor / Destructor
UTL_device::UTL_device(){
  //---------------------------

  //---------------------------
}
UTL_device::~UTL_device(){}

//Main function
void UTL_device::find_video_devices(){
  //---------------------------

  // Create a udev context
  struct udev* udev = udev_new();
  if (!udev) {
      std::cerr << "Failed to create udev context" << std::endl;
      return;
  }

  // Create a udev enumerator for video devices
  struct udev_enumerate* enumerate = udev_enumerate_new(udev);
  udev_enumerate_add_match_subsystem(enumerate, "video4linux");
  udev_enumerate_scan_devices(enumerate);

  // Get the list of devices
  struct udev_list_entry* devices = udev_enumerate_get_list_entry(enumerate);

  // Vector to store pairs of camera name and node
  std::vector<std::pair<std::string, std::string>> video_devices;

  // Iterate through the list and add information to the vector
  struct udev_list_entry* entry;
  udev_list_entry_foreach(entry, devices) {
    const char* path = udev_list_entry_get_name(entry);
    struct udev_device* device = udev_device_new_from_syspath(udev, path);

    const char* deviceNode = udev_device_get_devnode(device);
    const char* deviceName = udev_device_get_sysattr_value(device, "name");

    if (deviceName && deviceNode) {
      // Check if the camera name is already in the list
      auto it = std::find_if(video_devices.begin(), video_devices.end(), [&](const auto& pair) { return pair.first == deviceName; });

      // If not found, add to the list
      if (it == video_devices.end()) {
        video_devices.emplace_back(deviceName, deviceNode);
      }
    }

    udev_device_unref(device);
  }

  // Print the list
  this->vec_video_device.clear();
  for (const auto& camera : video_devices) {
    Struct_video_device device;
    device.name = camera.first;
    device.node = camera.second;
    this->vec_video_device.push_back(device);
  }

  // Cleanup
  udev_enumerate_unref(enumerate);
  udev_unref(udev);

  //---------------------------
}
