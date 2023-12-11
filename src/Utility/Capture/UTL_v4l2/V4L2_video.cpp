#include "V4L2_video.h"


//Constructor / Destructor
V4L2_video::V4L2_video(){
  //---------------------------

  this->video_loaded = false;

  //---------------------------
}
V4L2_video::~V4L2_video(){}

//Main function
void V4L2_video::load_video(string path){
  if(video_loaded) return;
  //---------------------------

  this->find_video_context(path);
  this->decode_video();

  //---------------------------
  this->video_loaded = true;
}
uint8_t* V4L2_video::acquire_next_frame(){
  int result;
  AVFrame* frame = nullptr;
  uint8_t* data = nullptr;
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
      cout << "[error] ffmpeg - avodec receive frame" << endl;
      return nullptr;
    }else{
      data = convert_frame_to_data(frame);
      this->frame_width = frame->width;
      this->frame_height = frame->height;

      this->clean_frame(frame);
    }

    //Free packet
    av_packet_unref(packet);
  }
  else{say("reboot");
    this->reboot_video();
  }

  //---------------------------
  return data;
}

//Video function
void V4L2_video::find_video_context(string path){
  //---------------------------

  this->video_context = avformat_alloc_context();
  bool ok = avformat_open_input(&video_context, path.c_str(), NULL, NULL);
  if(ok != 0){
    cout << "[error] ffmpeg - video not open" << endl;
  }

  //---------------------------
}
void V4L2_video::clean_video(){
  //---------------------------

  av_packet_free(&packet);
  avcodec_close(codec_context);
  avformat_close_input(&video_context);

  say("video with ffmpeg ok");

  //---------------------------
}
void V4L2_video::clean_frame(AVFrame* frame){
  //---------------------------

  av_frame_free(&frame);

  //---------------------------
}
void V4L2_video::reboot_video(){
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
void V4L2_video::decode_video(){
  //---------------------------

  //Read and decode a few frames to find missing information
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
}

//Subfunction
uint8_t* V4L2_video::convert_frame_to_data(AVFrame* frame){
  //---------------------------

  int stride = frame->width * 4;
  uint8_t* data = new uint8_t[stride * frame->height];
  this->convert_frame_to_RGB(frame, data, stride);

  //---------------------------
  return data;
}
void V4L2_video::convert_frame_to_RGB(AVFrame* frame, uint8_t* data, int stride){
  //---------------------------

  if(frame->format == AV_PIX_FMT_YUV420P){
    this->convert_YUV420P_to_RGB(frame, data, stride);
  }
  else{
    this->find_format_name(frame);
  }

  //---------------------------
}
void V4L2_video::convert_YUV420P_to_RGB(AVFrame* frame, uint8_t* output_data, int stride){
  //---------------------------

  int width = frame->width;
  int height = frame->height;
  int Y_stride = frame->linesize[0];
  int U_stride = frame->linesize[1];
  int V_stride = frame->linesize[2];

  #pragma omp parallel for
  for (int y = 0; y < height; y++){
    for (int x = 0; x < width; x++) {
      int Y = frame->data[0][y * Y_stride + x];
      int U = frame->data[1][y / 2 * U_stride + x / 2];
      int V = frame->data[2][y / 2 * V_stride + x / 2];

      int R, G, B;
      this->convert_YUV_to_RGB(Y, U, V, R, G, B);

      // Merge channels into VK_FORMAT_R8G8B8A8_UNORM
      uint8_t* pixel = &output_data[y * stride + x * 4];
      pixel[0] = static_cast<uint8_t>(R);
      pixel[1] = static_cast<uint8_t>(G);
      pixel[2] = static_cast<uint8_t>(B);
      pixel[3] = 255; // Fully opaque
    }
  }

  //---------------------------
}
void V4L2_video::convert_YUV_to_RGB(int Y, int U, int V, int& R, int& G, int& B){
  //---------------------------

  R = Y + 1.13983 * (V - 128);
  G = Y - 0.39465 * (U - 128) - 0.58060 * (V - 128);
  B = Y + 2.03211 * (U - 128);

  // Clamp RGB values to [0, 255]
  R = std::min(255, std::max(0, R));
  G = std::min(255, std::max(0, G));
  B = std::min(255, std::max(0, B));

  //---------------------------
}
void V4L2_video::find_format_name(AVFrame* frame){
  string result;
  //---------------------------

  switch (frame->format) {
    case AV_PIX_FMT_YUV420P: result = "AV_PIX_FMT_YUV420P";
    case AV_PIX_FMT_YUVJ420P: result = "AV_PIX_FMT_YUVJ420P";
    case AV_PIX_FMT_RGB24: result = "AV_PIX_FMT_RGB24";
    case AV_PIX_FMT_BGR24: result = "AV_PIX_FMT_BGR24";
    case AV_PIX_FMT_YUV422P: result = "AV_PIX_FMT_YUV422P";
    case AV_PIX_FMT_YUV444P: result = "AV_PIX_FMT_YUV444P";
    case AV_PIX_FMT_YUV410P: result = "AV_PIX_FMT_YUV410P";
    case AV_PIX_FMT_YUV411P: result = "AV_PIX_FMT_YUV411P";
    case AV_PIX_FMT_GRAY8: result = "AV_PIX_FMT_GRAY8";
    case AV_PIX_FMT_MONOWHITE: result = "AV_PIX_FMT_MONOWHITE";
    case AV_PIX_FMT_MONOBLACK: result = "AV_PIX_FMT_MONOBLACK";
    case AV_PIX_FMT_0RGB32: result = "AV_PIX_FMT_0RGB32";
    case AV_PIX_FMT_RGB0: result = "AV_PIX_FMT_RGB0";
    case AV_PIX_FMT_VDPAU: result = "AV_PIX_FMT_MJPEG";
    case AV_PIX_FMT_YUV420P10LE: result = "AV_PIX_FMT_YUV420P10LE";
    case AV_PIX_FMT_YUYV422: result = "AV_PIX_FMT_YUYV422";
    case AV_PIX_FMT_YUV422P10LE: result = "AV_PIX_FMT_YUV422P10LE";
    case AV_PIX_FMT_YUV444P10LE: result = "AV_PIX_FMT_YUV444P10LE";
    case AV_PIX_FMT_YUV420P12LE: result = "AV_PIX_FMT_YUV420P12LE";
    case AV_PIX_FMT_YUV422P12LE: result = "AV_PIX_FMT_YUV422P12LE";
    case AV_PIX_FMT_YUV444P12LE: result = "AV_PIX_FMT_YUV444P12LE";
    // Add more cases for other formats if needed
    default: result = "UNKNOWN_PIXEL_FORMAT";
  }

  //---------------------------
  cout<<result<<endl;
}
