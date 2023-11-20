#include "K4A_capture.h"

#define VENDOR_MICROSOFT 0x045E
#define ID_RGB 0x097D
#define ID_DEPTH 0x097C


//Constructor / Destructor
K4A_capture::K4A_capture(){
  //---------------------------

  this->device_config = new Struct_kinect_config();

  //---------------------------
}
K4A_capture::~K4A_capture(){}

//Main function
void K4A_capture::truc(){
  //---------------------------
static bool once = true;
  this->machin();

  if(once)
  this->chose();
once =false;
  //---------------------------
}

//Subfunction
void K4A_capture::machin(){
  //---------------------------
/*
  struct libusb_device_descriptor desc;
  libusb_context *usb_context;
  libusb_device **list_device; // pointer to pointer of device, used to retrieve a list of devices
  uint32_t color_device_count = 0;
  uint32_t depth_device_count = 0;

  // initialize library
  int result = libusb_init(&usb_context);
  if (result < 0) {
    cout << "Error calling libusb_init" << endl;
    return;
  }

  ssize_t count = libusb_get_device_list(usb_context, &list_device); // get the list of devices
  if (count > INT32_MAX) {
    cout << "List too large" << endl;
    return;
  }
  if (count <= 0) {
    cout << "No devices found" << endl;
    return;
  }

  // Loop through and count matching VID / PID
  for (int loop = 0; loop < count; loop++) {
    result = libusb_get_device_descriptor(list_device[loop], &desc);
    if (result < 0) {
      cout << "Error calling libusb_get_device_descriptor" << endl;
      libusb_free_device_list(list_device, 1);
      libusb_exit(usb_context);
      return;
    }

    // Count how many color or depth end points we find.
    if (desc.idVendor == VENDOR_MICROSOFT) {
      if (desc.idProduct == ID_RGB) {
        color_device_count += 1;
      }
      else if (desc.idProduct == ID_DEPTH) {
        depth_device_count += 1;
      }
    }
  }

  // free the list, unref the devices in it
  libusb_free_device_list(list_device, 1);

  // close the instance
  libusb_exit(usb_context);

  cout << "Color device count: " << color_device_count << endl;
  cout << "Depth device count: " << depth_device_count << endl;
*/
  //---------------------------
}
void K4A_capture::chose(){
  //---------------------------


  //---------------------------
}
void K4A_capture::open_selected_device(){
  //---------------------------

  try{
    if (selected_device_idx < 0){return;}
    selected_device = k4a::device::open(static_cast<uint32_t>(selected_device_idx));
  }
  catch (const int error){
    return;
  }

  //---------------------------
}
void K4A_capture::refresh_device_list(){
  //---------------------------

  //"(No available devices)"
  const uint32_t nb_device = k4a_device_get_installed_count();

  for (uint32_t i = 0; i < nb_device; i++){
    try{
      k4a::device device = k4a::device::open(i);
      connected_device.emplace_back(std::make_pair(i, device.get_serialnum()));
    }
    catch(const int error){
      continue;
    }
  }

  if (!connected_device.empty()){
    selected_device_idx = connected_device[0].first;
  }

  //---------------------------
}
void K4A_capture::make_k4a_configuration(Struct_kinect_config* config){
  //---------------------------

  config->k4a_config.color_format = config->color_format;
  config->k4a_config.color_resolution = config->enable_camera_color ? config->color_resolution : K4A_COLOR_RESOLUTION_OFF;
  config->k4a_config.depth_mode = config->enable_camera_depth ? config->depth_mode : K4A_DEPTH_MODE_OFF;
  config->k4a_config.camera_fps = config->camera_fps;
  config->k4a_config.depth_delay_off_color_usec = config->depth_delay_off_color_usec;
  config->k4a_config.wired_sync_mode = config->wired_sync_mode;
  config->k4a_config.subordinate_delay_off_master_usec = config->subordinate_delay_off_master_usec;
  config->k4a_config.disable_streaming_indicator = config->disable_streaming_indicator;
  config->k4a_config.synchronized_images_only = config->synchronized_images_only;

  //---------------------------
}
bool K4A_capture::start_camera(){
  //---------------------------

  if (camera_started){
    return false;
  }

  this->make_k4a_configuration(device_config);
  selected_device.start_cameras(&device_config->k4a_config);
  this->camera_started = true;

  /*this->thread_camera_polling = std14::make_unique<K4APollingThread>([selected_device, &camera_data_source, camera_pause, camera_started, false, false](bool firstRun){
    std::chrono::milliseconds pollingTimeout = CameraPollingTimeout;
    return PollSensor<k4a::capture>("Cameras", selected_device, &camera_data_source, camera_pause, camera_started, false,
      [](k4a::device *device, k4a::capture *capture, std::chrono::milliseconds timeout){return device->get_capture(capture, timeout);},
      [](k4a::device *device){device->stop_cameras();}, pollingTimeout);
  });*/

  return true;
}
