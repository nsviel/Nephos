#ifndef GUI_VIDEO_H
#define GUI_VIDEO_H

#include <UTL_specific/common.h>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

class GUI;
class VK_engine;


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
  VK_engine* vk_engine;

  VkDescriptorSet descriptor;
  AVFormatContext* format_context;
  AVCodecContext* codec_context;
  AVPacket* packet;
  bool video_loaded;
  int video_stream_idx;
};


#endif
