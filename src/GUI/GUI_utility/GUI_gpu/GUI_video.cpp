#include "GUI_video.h"

#include <GUI.h>
#include <Vulkan.h>
#include <VK_main/VK_engine.h>
#include <GUI_main/GUI_render/GUI_render.h>
#include <UTL_capture/UTL_video.h>


//Constructor / Destructor
GUI_video::GUI_video(GUI* gui){
  //---------------------------

  GUI_render* gui_render = gui->get_gui_render();
  Vulkan* gui_vulkan = gui_render->get_gui_vulkan();
  this->vk_engine = gui_vulkan->get_vk_engine();
  this->utl_video = new UTL_video();

  this->video_loaded = false;

  //---------------------------
}
GUI_video::~GUI_video(){}

//Main function
void GUI_video::draw_video(string path){
  //---------------------------

  utl_video->load_video_from_file(path);
  uint8_t* data = utl_video->acquire_next_frame();
  int width = utl_video->get_frame_width();
  int height = utl_video->get_frame_height();

  if(data != nullptr){
    static Struct_image* image = nullptr;

    if(image == nullptr){
      image = vk_engine->load_texture_from_data(data, width, height);
      VkDescriptorSet descriptor  = ImGui_ImplVulkan_AddTexture(image->sampler, image->view, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
      this->texture = reinterpret_cast<ImTextureID>(descriptor);
    }else{
      vk_engine->update_texture_from_data(image, data);
    }

  }

  this->display_frame();
  //this->clean_video();

  //---------------------------
}

//Subfunction
AVFrame* GUI_video::acquire_next_frame(){
  int result;
  AVFrame* frame = nullptr;
  //---------------------------

  //Get rid of sound data
  packet->stream_index = -1;
  while(packet->stream_index != video_stream_idx){
    result = av_read_frame(video_context, packet);
  }

  if(result >= 0){
    //Bring packet to frame decoder
    result = avcodec_send_packet(codec_context, packet);
    if(result < 0){
      cout << "[error] ffmpeg - AV codec send packet" << endl;
      return nullptr;
    }

    //Allocate AV frame
    frame = av_frame_alloc();
    if(!frame){
      cout << "[error] ffmpeg - frame memory allocation" << endl;
      return nullptr;
    }

    //Process or display the video frame here
    int frameFinished;
    result = avcodec_receive_frame(codec_context, frame);
    if(result != 0){
      cout<<"[error] decoding video"<<endl;
      return nullptr;
    }

    av_packet_unref(packet);
  }
  else{
    this->reboot_video();
  }

  //---------------------------
  return frame;
}
void GUI_video::load_video(string path){
  if(video_loaded) return;
  //---------------------------

  //Open video
  this->video_context = avformat_alloc_context();
  bool ok = avformat_open_input(&video_context, path.c_str(), NULL, NULL);
  if(ok != 0){
    cout << "[error] ffmpeg - video not open" << endl;
  }

  //Try to read and decode a few frames to find missing information
  int result = avformat_find_stream_info(video_context, NULL);
  if(result < 0){
    cout << "[error] ffmpeg - video information" << endl;
  }

  //Retrieve video stream index
  this->video_stream_idx = -1;
  for(int i=0; i<video_context->nb_streams; i++){
    if(video_context->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO){
      video_stream_idx = i;
      break;
    }
  }
  if(video_stream_idx == -1){
    cout << "[error] ffmpeg - do not find video stream index" << endl;
  }

  //Some stuff coding / decoding video
  AVCodec* codec = avcodec_find_decoder(video_context->streams[video_stream_idx]->codecpar->codec_id);
  this->codec_context = avcodec_alloc_context3(codec);

  //Copy the essential codec parameters (e.g., codec ID, width, height, pixel format, sample format)
  result = avcodec_parameters_to_context(codec_context, video_context->streams[video_stream_idx]->codecpar);
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
  avformat_close_input(&video_context);

  say("video with ffmpeg ok");

  //---------------------------
}
void GUI_video::reboot_video(){
  //---------------------------

  // Set the timebase for the video stream
  const AVRational stream_timebase = video_context->streams[video_stream_idx]->time_base;

  // Seek to the beginning of the video
  int64_t target_pts = 0;  // Target presentation timestamp (beginning of the video)
  int64_t seek_target = av_rescale_q(target_pts, AV_TIME_BASE_Q, stream_timebase);
  int seek_flags = 0;  // Flags (you can adjust them based on your requirements)

  int result = av_seek_frame(video_context, video_stream_idx, seek_target, seek_flags);
  if (result < 0) {
    cout << "[error] ffmpeg - Error seeking to the beginning" << endl;
  }

  //---------------------------
}
void GUI_video::display_frame(){
  //---------------------------

  ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
  ImGui::Image(texture, ImVec2{200,200});

  //---------------------------
}
