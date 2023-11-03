#include "GUI_video.h"

#include <GUI.h>
#include <Engine.h>


//Constructor / Destructor
GUI_video::GUI_video(GUI* gui){
  //---------------------------

  Engine* engine = gui->get_engine();
  this->gpu_texture = engine->get_gpu_texture();

  this->video_loaded = false;

  //---------------------------
}
GUI_video::~GUI_video(){}

//Main function
void GUI_video::draw_video(string path){
  //---------------------------

  this->load_video(path);
  this->acquire_next_frame();
  this->display_frame();
  //this->clean_video();

  //---------------------------
}

//Subfunction
void GUI_video::acquire_next_frame(){
  int result;
  //---------------------------

  packet->stream_index = -1;
  while(packet->stream_index != video_stream_idx){
    result = av_read_frame(format_context, packet);
  }

  if(result >= 0){
    //Send packet to frame decoder
    result = avcodec_send_packet(codec_context, packet);
    if(result < 0){
      cout << "[error] ffmpeg - AV codec send packet" << endl;
    }

    //Allocate AV frame
    AVFrame* frame = av_frame_alloc();
    if(!frame){
      cout << "[error] ffmpeg - frame memory allocation" << endl;
    }

    //Process or display the video frame here
    int frameFinished;
    result = avcodec_receive_frame(codec_context, frame);
    if(result == 0){
      Struct_image* image = gpu_texture->load_texture_from_frame(frame);
      this->descriptor  = ImGui_ImplVulkan_AddTexture(image->sampler, image->view, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
    }

    //Free AV frame
    av_frame_free(&frame);
    av_packet_unref(packet);
  }
  else{
    this->reboot_video();
  }

  //---------------------------
}
void GUI_video::load_video(string path){
  if(video_loaded) return;
  //---------------------------

  //Open video
  this->format_context = avformat_alloc_context();
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
  this->video_stream_idx = -1;
  for(int i=0; i<format_context->nb_streams; i++){
    if(format_context->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO){
      video_stream_idx = i;
      break;
    }
  }
  if(video_stream_idx == -1){
    cout << "[error] ffmpeg - do not find video stream index" << endl;
  }

  //Some stuff coding / decoding video
  AVCodec* codec = avcodec_find_decoder(format_context->streams[video_stream_idx]->codecpar->codec_id);
  this->codec_context = avcodec_alloc_context3(codec);

  //Copy the essential codec parameters (e.g., codec ID, width, height, pixel format, sample format)
  result = avcodec_parameters_to_context(codec_context, format_context->streams[video_stream_idx]->codecpar);
  if(result < 0){
    cout << "[error] ffmpeg - parameter to context" << endl;
  }

  result = avcodec_open2(codec_context, codec, NULL);
  if(result < 0){
    // Handle error
    cout << "[error] ffmpeg video decoder" << endl;
  }

  //Allocate AV packet
  this->packet = av_packet_alloc();
  if(!packet){
    cout << "[error] ffmpeg - AV packet allocation" << endl;
  }

  //---------------------------
  this->video_loaded = true;
}
void GUI_video::clean_video(){
  //---------------------------

  av_packet_free(&packet);
  avcodec_close(codec_context);
  avformat_close_input(&format_context);

  say("video with ffmpeg ok");

  //---------------------------
}
void GUI_video::reboot_video(){
  //---------------------------

  // Set the timebase for the video stream
  const AVRational stream_timebase = format_context->streams[video_stream_idx]->time_base;

  // Seek to the beginning of the video
  int64_t target_pts = 0;  // Target presentation timestamp (beginning of the video)
  int64_t seek_target = av_rescale_q(target_pts, AV_TIME_BASE_Q, stream_timebase);
  int seek_flags = 0;  // Flags (you can adjust them based on your requirements)

  int result = av_seek_frame(format_context, video_stream_idx, seek_target, seek_flags);
  if (result < 0) {
    cout << "[error] ffmpeg - Error seeking to the beginning" << endl;
  }

  //---------------------------
}
void GUI_video::display_frame(){
  //---------------------------

  ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
  ImGui::Image(descriptor, ImVec2{200,200});

  //---------------------------
}
