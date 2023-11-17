#include "GUI_capture.h"

#include <GUI_gpu/GUI_video.h>
#include <GUI_gpu/GUI_image.h>
#include <TAB_render/TAB_render.h>
#include <UTL_capture/UTL_device.h>
#include <GUI.h>


//Constructor / Destructor
GUI_capture::GUI_capture(GUI* gui, bool* show_window, string name) : BASE_panel(show_window, name){
  //---------------------------

  this->gui_image = new GUI_image(gui);
  this->gui_video = new GUI_video(gui);
  this->gui = gui;
  this->utl_device = new UTL_device();

  this->stream_node = "";

  //---------------------------
}
GUI_capture::~GUI_capture(){}

//Main function
void GUI_capture::design_panel(){
  //---------------------------

  this->capture_devices();
  this->capture_command();
  this->truc();

  //---------------------------
}

//Subfunction
void GUI_capture::capture_devices(){
  //---------------------------

  utl_device->find_video_devices();
  vector<Struct_video_device> vec_devices = utl_device->get_vec_video_device();

  ImGuiTableFlags flags;
  flags |= ImGuiTableFlags_Borders;
  flags |= ImGuiTableFlags_RowBg;
  static int selected_device = -1;
  if (ImGui::BeginTable("database_view", 2, flags)) {
    for (int i = 0; i < vec_devices.size(); i++) {
      Struct_video_device& device = vec_devices[i];

      ImGui::TableNextRow();
      ImGui::TableNextColumn();

      ImGui::PushID(device.name.c_str());

      // Use ImGui::Selectable to make the row selectable
      if (ImGui::Selectable(device.name.c_str(), selected_device == i, ImGuiSelectableFlags_SpanAllColumns)) {
        this->stream_node = device.node;
        gui_video->restart_video();
        selected_device = i;
      }

      ImGui::TableNextColumn();
      ImGui::Text("%s", device.node.c_str());

      ImGui::PopID();
    }

    ImGui::EndTable();
  }

  //---------------------------
}
void GUI_capture::capture_command(){
  ImGuiIO& io = ImGui::GetIO();
  //---------------------------

  gui_video->draw_video(stream_node);
  //gui_image->draw_image_static("../media/vulkano.jpg");

  //---------------------------
}
void GUI_capture::truc(){
  //---------------------------




/*
  DeviceDescriptor devices[] = {
      {0x045E, 0x02C2}, // K4A_RGB_PID
      {0x045E, 0x02C4}, // K4A_DEPTH_PID
      // Add more devices if needed
  };

  uint32_t color_device_count = 0;
  uint32_t depth_device_count = 0;

  size_t device_count = sizeof(devices) / sizeof(devices[0]);

  for (size_t i = 0; i < device_count; ++i)
  {
      // Count how many color or depth devices match VID/PID
      if (devices[i].idVendor == 0x045E && devices[i].idProduct == 0x02C2)
      {
          color_device_count += 1;
      }
      else if (devices[i].idVendor == 0x045E && devices[i].idProduct == 0x02C4)
      {
          depth_device_count += 1;
      }
  }

  // Color or Depth device may be in a bad state, so return the larger count
  uint32_t total_device_count = std::max(color_device_count, depth_device_count);

  std::cout << "Total device count: " << depth_device_count << std::endl;
*/
/*
  struct libusb_device_descriptor desc;
    libusb_context *libusb_ctx;
    libusb_device **dev_list; // pointer to pointer of device, used to retrieve a list of devices
    ssize_t count;            // holding number of devices in list
    int err;
    uint32_t color_device_count = 0;
    uint32_t depth_device_count = 0;

    if (p_device_count == NULL)
    {
        LOG_ERROR("Error p_device_count is NULL", 0);
        return K4A_RESULT_FAILED;
    }

    *p_device_count = 0;
    // initialize library
    if ((err = libusb_init(&libusb_ctx)) < 0)
    {
        LOG_ERROR("Error calling libusb_init, result:%s", libusb_error_name(err));
        return K4A_RESULT_FAILED;
    }

    // We disable all LIBUSB logging for this function, which only used this local context. LIBUSB (on Windows)
    // generates errors when a device is detached moments before this is called.
    libusb_logging_disable(libusb_ctx);

    count = libusb_get_device_list(libusb_ctx, &dev_list); // get the list of devices
    if (count > INT32_MAX)
    {
        LOG_ERROR("List too large", 0);
        return K4A_RESULT_FAILED;
    }
    if (count <= 0)
    {
        LOG_ERROR("No devices found", 0);
        return K4A_RESULT_FAILED;
    }

    // Loop through and count matching VID / PID
    for (int loop = 0; loop < count; loop++)
    {
        result = K4A_RESULT_FROM_LIBUSB(libusb_get_device_descriptor(dev_list[loop], &desc));
        if (K4A_FAILED(result))
        {
            break;
        }

        //  Count how many color or depth end points we find.
        if (desc.idVendor == K4A_MSFT_VID)
        {
            if (desc.idProduct == K4A_RGB_PID)
            {
                color_device_count += 1;
            }
            else if (desc.idProduct == K4A_DEPTH_PID)
            {
                depth_device_count += 1;
            }
        }
    }
    // free the list, unref the devices in it
    libusb_free_device_list(dev_list, (int)count);

    // close the instance
    libusb_exit(libusb_ctx);

    // Color or Depth end point my be in a bad state so we cound both and return the larger count
    *p_device_count = color_device_count > depth_device_count ? color_device_count : depth_device_count;
*/

  //---------------------------
}
