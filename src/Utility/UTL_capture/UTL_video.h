#ifndef UTL_VIDEO_H
#define UTL_VIDEO_H

#include <UTL_specific/common.h>
extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

using namespace std;


class UTL_video
{
public:
  //Constructor / Destructor
  UTL_video();
  ~UTL_video();

public:
  //Main function
  AVFrame* acquire_next_frame();
  void load_video_from_file(string path);
  void clean_video();
  void clean_frame(AVFrame* frame);
  void reboot_video();
  void decode_video();
  uint8_t* convert_frame_to_data(AVFrame* frame);
  void convert_YUV_to_RGB(int Y, int U, int V, int& R, int& G, int& B);
  void convert_YUV420P_to_RGB(AVFrame* frame, uint8_t* output_data, int output_stride);

private:
  AVFormatContext* video_context;
  AVCodecContext* codec_context;
  AVPacket* packet;
  bool video_loaded;
  int video_stream_idx;
};

#endif
