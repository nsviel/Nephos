#include "GUI_video.h"

#include <Engine.h>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}


//Constructor / Destructor
GUI_video::GUI_video(Engine* engine){
  //---------------------------

  this->gpu_texture = engine->get_gpu_texture();
  this->path = "/home/aeter/Desktop/Dev/Nephos/media/vulkano.mp4";

  //this->display_video_ffmpeg("truc");
  //---------------------------
}
GUI_video::~GUI_video(){}

//Main function
void GUI_video::display_video_ffmpeg(string path_video){
  //---------------------------


  avformat_network_init(); // Initialize network components (if needed)

  AVFormatContext* formatContext = avformat_alloc_context();

  if (avformat_open_input(&formatContext, path.c_str(), NULL, NULL) != 0) {
      // Handle error
      cout << "[error] ffmped video decoder" << endl;
  }

  if (avformat_find_stream_info(formatContext, NULL) < 0) {
      // Handle error
      cout << "[error] ffmped video decoder" << endl;
  }

  int videoStream = -1;
  for (unsigned int i = 0; i < formatContext->nb_streams; i++) {
      if (formatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
          videoStream = i;
          break;
      }
  }

  if (videoStream == -1) {
      // Handle error
      cout << "[error] ffmped video decoder" << endl;
  }

  AVCodec* codec = avcodec_find_decoder(formatContext->streams[videoStream]->codecpar->codec_id);
  AVCodecContext* codecContext = avcodec_alloc_context3(codec);

  if (avcodec_parameters_to_context(codecContext, formatContext->streams[videoStream]->codecpar) < 0) {
      // Handle error
      cout << "[error] ffmped video decoder" << endl;
  }

  if (avcodec_open2(codecContext, codec, NULL) < 0) {
      // Handle error
      cout << "[error] ffmped video decoder" << endl;
  }

  AVPacket* packet = av_packet_alloc();

  if (!packet) {
      // Handle memory allocation error
      cout << "[error] ffmped video decoder" << endl;
  }

  while (av_read_frame(formatContext, packet) >= 0) {
      if (packet->stream_index == videoStream) {
          AVFrame* frame = av_frame_alloc();

          if (!frame) {
              // Handle memory allocation error
              break;
          }

          int frameFinished;
          if (avcodec_receive_frame(codecContext, frame) >= 0) {
              // Process or display the video frame here
          }

          av_frame_free(&frame);
      }

      av_packet_unref(packet);
  }

  av_packet_free(&packet);
  avcodec_close(codecContext);
  avformat_close_input(&formatContext);

  say("video with ffmpeg ok");

  //---------------------------
}

//Subfunction
