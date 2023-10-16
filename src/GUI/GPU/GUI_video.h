#ifndef GUI_VIDEO_H
#define GUI_VIDEO_H

#include <Specific/common.h>
#include <GPU/GPU_texture.h>
#include <vlc/vlc.h>

class Engine;


class GUI_video
{
public:
  //Constructor / Destructor
  GUI_video(Engine* engine);
  ~GUI_video();

public:
  //Main function
  void display_video_vlc(string path);
  void display_video_ffmpeg(string path);

private:
  GPU_texture* gpu_texture;

  libvlc_media_player_t* mediaPlayer;
};


#endif
