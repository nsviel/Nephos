#pragma once

#include <Utility/Specific/Common.h>
extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavdevice/avdevice.h>
}

using namespace std;


namespace util::v4l2{

class Video
{
public:
  //Constructor / Destructor
  Video();
  ~Video();

public:
  //Main function
  void load_video(string path);
  uint8_t* acquire_next_frame();

  //Video function
  void find_video_context(string path);
  void clean_video();
  void clean_frame(AVFrame* frame);
  void reboot_video();
  void decode_video();

  //Subfunction
  uint8_t* convert_frame_to_data(AVFrame* frame);
  void convert_frame_to_RGB(AVFrame* frame, uint8_t* data, int stride);
  void convert_YUV420P_to_RGB(AVFrame* frame, uint8_t* data, int stride);
  void convert_YUV_to_RGB(int Y, int U, int V, int& R, int& G, int& B);
  void find_format_name(AVFrame* frame);

  inline int get_frame_width(){return frame_width;}
  inline int get_frame_height(){return frame_height;}

private:
  AVFormatContext* video_context = nullptr;
  AVCodecContext* codec_context;
  AVPacket* packet;
  bool video_loaded;
  int video_stream_idx;
  int frame_width = 0;
  int frame_height = 0;
};

}
