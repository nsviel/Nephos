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
  uint8_t* acquire_next_frame();
  void load_video_from_file(string path);

  //Video function
  void clean_video();
  void clean_frame(AVFrame* frame);
  void reboot_video();
  void decode_video();

  //Subfunction
  uint8_t* convert_frame_to_data(AVFrame* frame);
  void convert_YUV_to_RGB(int Y, int U, int V, int& R, int& G, int& B);
  void convert_YUV420P_to_RGB(AVFrame* frame, uint8_t* output_data, int output_stride);

  inline int get_frame_width(){return frame_width;}
  inline int get_frame_height(){return frame_height;}

private:
  AVFormatContext* video_context;
  AVCodecContext* codec_context;
  AVPacket* packet;
  bool video_loaded;
  int video_stream_idx;
  int frame_width = 0;
  int frame_height = 0;
};

#endif
