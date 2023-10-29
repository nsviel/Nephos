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

  //Open video
  AVFormatContext* format_context = avformat_alloc_context();
  bool ok = avformat_open_input(&format_context, path.c_str(), NULL, NULL);
  if(ok != 0){
    cout << "[error] ffmpeg - video not open" << endl;
  }

  //Try to read and decode a few frames to find missing information
  int result = avformat_find_stream_info(format_context, NULL);
  if(result < 0){
    cout << "[error] ffmpeg - video information" << endl;
  }

  //Retrieve video stream index
  int video_stream = -1;
  for(int i=0; i<format_context->nb_streams; i++){
    if(format_context->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO){
      video_stream = i;
      break;
    }
  }
  if (video_stream == -1) {
    cout << "[error] ffmpeg - do not find video stream index" << endl;
  }

  //Some stuff coding / decoding video
  AVCodec* codec = avcodec_find_decoder(format_context->streams[video_stream]->codecpar->codec_id);
  AVCodecContext* codec_context = avcodec_alloc_context3(codec);

  //Copy the essential codec parameters (e.g., codec ID, width, height, pixel format, sample format)
  result = avcodec_parameters_to_context(codec_context, format_context->streams[video_stream]->codecpar);
  if(result < 0){
    cout << "[error] ffmpeg - parameter to context" << endl;
  }

  result = avcodec_open2(codec_context, codec, NULL);
  if(result < 0){
    // Handle error
    cout << "[error] ffmpeg video decoder" << endl;
  }

  //---------------

  //Allocate AV packet
  AVPacket* packet = av_packet_alloc();
  if(!packet){
    cout << "[error] ffmpeg - AV packet allocation" << endl;
  }

  //Video loop
  while(av_read_frame(format_context, packet) >= 0){
    if(packet->stream_index == video_stream){
      //Allocate AV frame
      AVFrame* frame = av_frame_alloc();
      if(!frame){
        cout << "[error] ffmpeg - frame memory allocation" << endl;
        break;
      }

      //Process or display the video frame
      int frameFinished;
      if(avcodec_receive_frame(codec_context, frame) >= 0){
        // Process or display the video frame here
      }

      //Free AV frame
      av_frame_free(&frame);
    }

    av_packet_unref(packet);
  }

  //Clean all AV stuff
  av_packet_free(&packet);
  avcodec_close(codec_context);
  avformat_close_input(&format_context);

  say("video with ffmpeg ok");

  //---------------------------
}

//Subfunction
