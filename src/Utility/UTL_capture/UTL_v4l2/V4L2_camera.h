#ifndef V4L2_CAMERA_H
#define V4L2_CAMERA_H

#include <UTL_specific/common.h>
#include <UTL_base/Struct_video.h>
extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavdevice/avdevice.h>
}

using namespace std;
#include <libudev.h>


class V4L2_camera
{
public:
  //Constructor / Destructor
  V4L2_camera();
  ~V4L2_camera();

public:
  //Main function
  void load_stream(string path);

  //Video function
  void find_video_context(string path);
  void decode_video();
  void clean_video();

  //Subfunction
  uint8_t* convert_frame_to_data(AVFrame* frame);
  void convert_frame_to_RGB(AVFrame* frame, uint8_t* data, int stride);
  void convert_YUV420P_to_RGB(AVFrame* frame, uint8_t* data, int stride);
  void convert_YUV_to_RGB(int Y, int U, int V, int& R, int& G, int& B);
  void find_format_name(AVFrame* frame);
  void find_video_information();
  void thread_read_frame();
  void thread_video_device();
  bool check_device_connection();
  void find_camera_devices();

  inline uint8_t* get_frame_data(){check_device_connection();return data;}
  inline int get_frame_width(){return frame_width;}
  inline int get_frame_height(){return frame_height;}

private:
  std::vector<std::pair<std::string, std::string>> list_camera_devices;
  data::Video struct_video;
  AVFormatContext* video_context = nullptr;
  AVCodecContext* codec_context;
  AVPacket* packet;

  string path_stream;
  bool stream_loaded;
  bool stream_active;
  bool thread_running;
  int video_stream_idx;
  int frame_width = 0;
  int frame_height = 0;
  std::thread thread_frame;
  std::thread thread_device;
  uint8_t* data = nullptr;
};

#endif
