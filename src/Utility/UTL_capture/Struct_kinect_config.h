#ifndef STRUCT_KINECT_CONFIG_H
#define STRUCT_KINECT_CONFIG_H

#include <k4a/k4a.hpp>


k4a_device_configuration_t K4ADeviceConfiguration::ToK4ADeviceConfiguration() const
{
    k4a_device_configuration_t deviceConfig;

    deviceConfig.color_format = ColorFormat;
    deviceConfig.color_resolution = EnableColorCamera ? ColorResolution : K4A_COLOR_RESOLUTION_OFF;
    deviceConfig.depth_mode = EnableDepthCamera ? DepthMode : K4A_DEPTH_MODE_OFF;
    deviceConfig.camera_fps = Framerate;

    deviceConfig.depth_delay_off_color_usec = DepthDelayOffColorUsec;
    deviceConfig.wired_sync_mode = WiredSyncMode;
    deviceConfig.subordinate_delay_off_master_usec = SubordinateDelayOffMasterUsec;

    deviceConfig.disable_streaming_indicator = DisableStreamingIndicator;
    deviceConfig.synchronized_images_only = SynchronizedImagesOnly;

    return deviceConfig;
}

struct Struct_kinect_config{
  //---------------------------

  // Fields that convert to k4a_device_configuration_t
  //
  bool EnableColorCamera = true;
  bool EnableDepthCamera = true;
  k4a_image_format_t ColorFormat = K4A_IMAGE_FORMAT_COLOR_BGRA32;
  k4a_color_resolution_t ColorResolution = K4A_COLOR_RESOLUTION_720P;
  k4a_depth_mode_t DepthMode = K4A_DEPTH_MODE_NFOV_UNBINNED;
  k4a_fps_t Framerate = K4A_FRAMES_PER_SECOND_30;

  int32_t DepthDelayOffColorUsec = 0;
  k4a_wired_sync_mode_t WiredSyncMode = K4A_WIRED_SYNC_MODE_STANDALONE;
  uint32_t SubordinateDelayOffMasterUsec = 0;
  bool DisableStreamingIndicator = false;
  bool SynchronizedImagesOnly = true;

  // UI-only fields that do not map to k4a_device_configuration_t
  //
  bool EnableImu = true;
  bool EnableMicrophone = true;

  // Convert to a k4a_device_configuration_t suitable for passing to the K4A API
  //
  k4a_device_configuration_t ToK4ADeviceConfiguration() const;

  //---------------------------
};



#endif
