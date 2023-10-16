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

  //---------------------------
}
GUI_video::~GUI_video(){}

//Main function
void GUI_video::display_video_vlc(string path){
  //---------------------------

  static bool once = true;
  if(once){
    libvlc_instance_t* vlcInstance = libvlc_new(0, nullptr);
    libvlc_media_t* media = libvlc_media_new_path(vlcInstance, path.c_str());
    this->mediaPlayer = libvlc_media_player_new_from_media(media);
    libvlc_media_release(media);
  }
  once = false;


  libvlc_media_player_play(mediaPlayer);


  //---------------------------
}
void GUI_video::display_video_ffmpeg(string path){
  //---------------------------


  AVFormatContext* formatContext = avformat_alloc_context();
  if (avformat_open_input(&formatContext, path.c_str(), nullptr, nullptr) != 0) {
      // Handle error
  }

  if (avformat_find_stream_info(formatContext, nullptr) < 0) {
      // Handle error
  }

  int videoStream = -1;
  for (int i = 0; i < formatContext->nb_streams; i++) {
      if (formatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
          videoStream = i;
          break;
      }
  }

  if (videoStream == -1) {
      // Handle error: No video stream found
  }

  AVCodecParameters* codecParameters = formatContext->streams[videoStream]->codecpar;
  AVCodec* codec = avcodec_find_decoder(codecParameters->codec_id);
  AVCodecContext* codecContext = avcodec_alloc_context3(codec);
  avcodec_parameters_to_context(codecContext, codecParameters);
  avcodec_open2(codecContext, codec, nullptr);

  AVPacket packet;
  AVFrame* frame = av_frame_alloc();

  while (av_read_frame(formatContext, &packet) >= 0) {
      if (packet.stream_index == videoStream) {
          avcodec_send_packet(codecContext, &packet);
          avcodec_receive_frame(codecContext, frame);

          // Process and render the frame with Vulkan and ImGui
          // Use frame->data for the frame data
sayHello();
          av_frame_unref(frame);
      }
      av_packet_unref(&packet);
  }

  av_frame_free(&frame);
  avcodec_free_context(&codecContext);
  avformat_close_input(&formatContext);

  //---------------------------
}

//Subfunction
