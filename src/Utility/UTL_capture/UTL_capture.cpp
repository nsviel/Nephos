#include "UTL_capture.h"

#define VENDOR_MICROSOFT 0x045E
#define ID_RGB 0x097D
#define ID_DEPTH 0x097C


//Constructor / Destructor
UTL_capture::UTL_capture(){
  //---------------------------


  //---------------------------
}
UTL_capture::~UTL_capture(){}

//Main function
void UTL_capture::truc(){
  //---------------------------

  this->machin();
  this->chose();

  //---------------------------
}

//Subfunction
void UTL_capture::machin(){
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
void UTL_capture::chose(){
  //---------------------------

  // Initialize the Azure Kinect sensor
  k4a_device_t device = NULL;
  k4a_device_configuration_t config = K4A_DEVICE_CONFIG_INIT_DISABLE_ALL;
  config.camera_fps = K4A_FRAMES_PER_SECOND_30;
/*
  if (K4A_FAILED(k4a_device_open(0, &device)) ||
      K4A_FAILED(k4a_device_start_cameras(device, &config))) {
      std::cerr << "Failed to open or start the device" << std::endl;
      return;
  }

  // Capture frames for a short duration
  std::chrono::seconds captureDuration(5);
  auto startTime = std::chrono::high_resolution_clock::now();

  while (std::chrono::high_resolution_clock::now() - startTime < captureDuration) {
      k4a_capture_t capture = NULL;
      if (k4a_device_get_capture(device, &capture, K4A_WAIT_INFINITE) == K4A_WAIT_RESULT_SUCCEEDED) {
        sayHello();
          // Access color and depth frames here if needed
          // k4a_image_t colorImage = k4a_capture_get_color_image(capture);
          // k4a_image_t depthImage = k4a_capture_get_depth_image(capture);

          // Process the frames...

          // Release the capture
          k4a_capture_release(capture);
      }

      // Sleep for a short time to avoid busy-waiting
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  // Stop the device and close it
  k4a_device_stop_cameras(device);
  k4a_device_close(device);
*/
  //---------------------------
}
