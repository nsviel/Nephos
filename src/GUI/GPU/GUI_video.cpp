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

  AVPacket packet;
  AVFrame* frame;
  AVCodecContext* codecContext ;
  AVFormatContext* formatContext ;
  int videoStream = -1;

  static bool once = true;
  if(once){
     formatContext = avformat_alloc_context();
    if (avformat_open_input(&formatContext, path.c_str(), nullptr, nullptr) != 0) {
      cout<<"[error] Problem reading video file"<<endl;
    }

    if (avformat_find_stream_info(formatContext, nullptr) < 0) {
      cout<<"[error] Problem finding video stream"<<endl;
    }


    for (int i = 0; i < formatContext->nb_streams; i++) {
      if (formatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
        videoStream = i;
        break;
      }
    }

    if (videoStream == -1) {
      cout<<"[error] No video stream found"<<endl;
    }

    AVCodecParameters* codecParameters = formatContext->streams[videoStream]->codecpar;
    AVCodec* codec = avcodec_find_decoder(codecParameters->codec_id);
    codecContext = avcodec_alloc_context3(codec);
    avcodec_parameters_to_context(codecContext, codecParameters);
    avcodec_open2(codecContext, codec, nullptr);


     frame = av_frame_alloc();

    av_read_frame(formatContext, &packet);
  }
  once = false;


//while (av_read_frame(formatContext, &packet) >= 0) {
    if (packet.stream_index == videoStream) {
      avcodec_send_packet(codecContext, &packet);
      avcodec_receive_frame(codecContext, frame);

      // Process and render the frame with Vulkan and ImGui
      // Use frame->data for the frame data
say("GUI VIDEO Work In Progress");



//      av_frame_unref(frame);
    }
//    av_packet_unref(&packet);
//  }

/*
  av_frame_free(&frame);
  avcodec_free_context(&codecContext);
  avformat_close_input(&formatContext);*/

  //---------------------------
}

//Subfunction
