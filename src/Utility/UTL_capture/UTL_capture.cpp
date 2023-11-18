#include "UTL_capture.h"

#define MSFT_VID 0x045E
#define RGB_PID 0x097D
#define DEPTH_PID 0x097C


//Constructor / Destructor
UTL_capture::UTL_capture(){
  //---------------------------


  //---------------------------
}
UTL_capture::~UTL_capture(){}

//Main function
void UTL_capture::truc(){
  //---------------------------

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
    if (desc.idVendor == MSFT_VID) {
      if (desc.idProduct == RGB_PID) {
        color_device_count += 1;
      }
      else if (desc.idProduct == DEPTH_PID) {
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

  //---------------------------
}
