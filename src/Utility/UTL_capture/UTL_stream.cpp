#include "UTL_stream.h"


//Constructor / Destructor
UTL_stream::UTL_stream(){
  //---------------------------

  this->video_loaded = false;

  //---------------------------
}
UTL_stream::~UTL_stream(){}

//Main function
void UTL_stream::load_stream(string path){
  if(video_loaded) return;
  //---------------------------

  this->find_video_context(path);
  this->decode_video();
  this->find_video_information();

  //---------------------------
  this->video_loaded = true;
}
uint8_t* UTL_stream::acquire_next_frame(){
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
    }

    //Free packet
    av_frame_free(&frame);
    av_packet_unref(packet);
  }
  else{say("reboot");
    this->reboot_video();
  }

  //---------------------------
  return data;
}

//Video function
void UTL_stream::find_video_context(string path){
  //---------------------------

  avdevice_register_all(); // for device

  string dev_name = "/dev/video0"; // here mine is video0 , it may vary.
  AVInputFormat* inputFormat = av_find_input_format("v4l2");
  AVDictionary* options = NULL;
  av_dict_set(&options, "framerate", "30", 0);

  // check video source
  video_context = avformat_alloc_context();
  bool ok = avformat_open_input(&video_context, dev_name.c_str(), inputFormat, NULL);
  if(ok != 0){
    cout<<"\nOops, could'nt open video source\n\n";
    return;
  }

  //---------------------------
}
void UTL_stream::decode_video(){
  //---------------------------

  //Read and decode a few frames to find missing information
  int result = avformat_find_stream_info(video_context, NULL);
  if(result < 0){
    cout << "[error] ffmpeg - video information" << endl;
  }


sayHello();
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
sayHello();
  //Some stuff coding / decoding video
  AVCodecParameters* codecParameters = video_context->streams[video_stream_idx]->codecpar;
  const AVCodec* codec = avcodec_find_decoder(codecParameters->codec_id);
  if (codec == NULL) {
    cout << "[error] ffmpeg - do not find video stream index" << endl;
  }

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
void UTL_stream::clean_video(){
  //---------------------------

  av_packet_free(&packet);
  avcodec_close(codec_context);
  avformat_close_input(&video_context);

  say("video with ffmpeg ok");

  //---------------------------
}
void UTL_stream::reboot_video(){
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

//Subfunction
uint8_t* UTL_stream::convert_frame_to_data(AVFrame* frame){
  //---------------------------

  int stride = frame->width * 4;
  uint8_t* data = new uint8_t[stride * frame->height];
  //this->convert_frame_to_RGB(frame, data, stride);
  this->convert_YUV420P_to_RGB(frame, data, stride);

  //---------------------------
  return data;
}
void UTL_stream::convert_frame_to_RGB(AVFrame* frame, uint8_t* data, int stride){
  //---------------------------

  if(frame->format == AV_PIX_FMT_YUV420P){
    this->convert_YUV420P_to_RGB(frame, data, stride);
  }
  else{
    this->find_format_name(frame);
  }

  //---------------------------
}
void UTL_stream::convert_YUV420P_to_RGB(AVFrame* frame, uint8_t* output_data, int stride){
  //---------------------------

  int width = frame->width;
  int height = frame->height;
  int YUYV_stride = frame->linesize[0];

  #pragma omp parallel for
  for (int y = 0; y < height; y++) {
      for (int x = 0; x < width * 2; x += 4) {  // Adjusted loop increment for YUYV422
          int Y1 = frame->data[0][y * YUYV_stride + x];
          int U = frame->data[0][y * YUYV_stride + x + 1];
          int Y2 = frame->data[0][y * YUYV_stride + x + 2];
          int V = frame->data[0][y * YUYV_stride + x + 3];

          int R1, G1, B1, R2, G2, B2;
          this->convert_YUV_to_RGB(Y1, U, V, R1, G1, B1);
          this->convert_YUV_to_RGB(Y2, U, V, R2, G2, B2);

          // Merge channels into VK_FORMAT_R8G8B8A8_UNORM
          uint8_t* pixel1 = &output_data[y * stride + x * 2];
          uint8_t* pixel2 = &output_data[y * stride + (x + 2) * 2];

          pixel1[0] = static_cast<uint8_t>(R1);
          pixel1[1] = static_cast<uint8_t>(G1);
          pixel1[2] = static_cast<uint8_t>(B1);
          pixel1[3] = 255;  // Fully opaque

          pixel2[0] = static_cast<uint8_t>(R2);
          pixel2[1] = static_cast<uint8_t>(G2);
          pixel2[2] = static_cast<uint8_t>(B2);
          pixel2[3] = 255;  // Fully opaque
      }
  }

  //---------------------------
}
void UTL_stream::convert_YUV_to_RGB(int Y, int U, int V, int& R, int& G, int& B){
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
void UTL_stream::find_format_name(AVFrame* frame){
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

  if(result != "UNKNOWN_PIXEL_FORMAT"){
    cout<<result<<endl;
  }

  //---------------------------
}
void UTL_stream::find_video_information(){
  //---------------------------

  struct_video.start_time = video_context->start_time / 1000000;
  if(video_context->duration > 0){
    struct_video.duration = video_context->duration;
  }else{
    struct_video.duration = -1;
  }
  struct_video.bit_rate = video_context->bit_rate / 1000; //kb/s

  // Print information about each stream
  for (unsigned int i = 0; i < video_context->nb_streams; i++) {
    AVStream* stream = video_context->streams[i];

    if (stream->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
      struct_video.width = stream->codecpar->width;
      struct_video.height = stream->codecpar->height;
      struct_video.bit_rate = stream->codecpar->bit_rate; //kb/s
      struct_video.fps = av_q2d(stream->avg_frame_rate);
    } else if (stream->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
      std::cout << "Audio: ";
      // Add audio stream information
    } else {
      std::cout << "Other type of stream" << std::endl;
    }
  }

  //---------------------------
}
