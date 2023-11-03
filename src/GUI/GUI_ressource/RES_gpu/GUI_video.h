#ifndef GUI_VIDEO_H
#define GUI_VIDEO_H

#include <ELE_specific/common.h>
#include <ENG_gpu/GPU_texture.h>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

class GUI;


class GUI_video
{
public:
  //Constructor / Destructor
  GUI_video(GUI* gui);
  ~GUI_video();

public:
  //Main function
  void draw_video(string path);

  //Subfunction
  void acquire_next_frame();
  void load_video(string path);
  void clean_video();
  void reboot_video();
  void display_frame();

private:
  GPU_texture* gpu_texture;

  VkDescriptorSet descriptor;
  AVFormatContext* format_context;
  AVCodecContext* codec_context;
  AVPacket* packet;
  bool video_loaded;
  int video_stream_idx;
};


#endif
