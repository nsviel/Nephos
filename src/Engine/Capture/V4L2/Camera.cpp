#include "Camera.h"

#include <Utility/Namespace.h>


namespace util::v4l2{

//Constructor / Destructor
Camera::Camera(){
  //---------------------------

  this->stream_loaded = false;
  this->stream_active = false;

  //---------------------------
}
Camera::~Camera(){}

//Main function
void Camera::load_stream(string path){
  if(stream_loaded && stream_active || path == "") return;
  //---------------------------

  this->find_camera_devices();
  this->find_video_context(path);
  this->find_video_information();
  this->decode_video();

  //Start reading thread
  if(thread_running == false){
    this->thread_frame = std::thread(&Camera::thread_read_frame, this);
  }

  //---------------------------
  this->stream_loaded = true;
}

//Video function
void Camera::find_video_context(string path){
  this->path_stream = path;
  //---------------------------

  //Check if device exists
  if(!utl::fct::file::is_device_connected(path_stream)) return;

  avdevice_register_all(); // for device

  AVInputFormat* inputFormat = av_find_input_format("v4l2");
  AVDictionary* options = NULL;
  av_dict_set(&options, "video_size", "1280x720", 0); // Set the desired resolution
  av_dict_set(&options, "input_format", "mjpeg", 0); // Set the pixel format to MJPEG

  // check video source
  this->video_context = avformat_alloc_context();
  bool ok = avformat_open_input(&video_context, path.c_str(), inputFormat, NULL);
  if(ok != 0 || video_context == nullptr){
    this->stream_active = false;
  }else{
    this->stream_active = true;
  }

  //---------------------------
}
void Camera::decode_video(){
  if(stream_active == false) return;
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
void Camera::clean_video(){
  //---------------------------

  if(!stream_loaded) return;

  this->stream_loaded = false;
  this->stream_active = false;
  this->thread_running = false;
  this->thread_frame.join();

  av_packet_free(&packet);
  avcodec_close(codec_context);
  avformat_close_input(&video_context);
  avformat_free_context(video_context);

  this->video_context = nullptr;

  //---------------------------
}

//Subfunction
uint8_t* Camera::convert_frame_to_data(AVFrame* frame){
  //---------------------------

  int stride = frame->width * 4;
  uint8_t* data = new uint8_t[stride * frame->height];
  //this->convert_frame_to_RGB(frame, data, stride);
  this->convert_YUV420P_to_RGB(frame, data, stride);

  //---------------------------
  return data;
}
void Camera::convert_frame_to_RGB(AVFrame* frame, uint8_t* data, int stride){
  //---------------------------

  if(frame->format == AV_PIX_FMT_YUV420P){
    this->convert_YUV420P_to_RGB(frame, data, stride);
  }
  else{
    this->find_format_name(frame);
  }

  //---------------------------
}
void Camera::convert_YUV420P_to_RGB(AVFrame* frame, uint8_t* output_data, int stride){
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
void Camera::convert_YUV_to_RGB(int Y, int U, int V, int& R, int& G, int& B){
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
void Camera::find_format_name(AVFrame* frame){
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
void Camera::find_video_information(){
  if(stream_active == false) return;
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
void Camera::thread_read_frame(){
  //---------------------------

  int result;
  AVFrame* frame = nullptr;
  thread_running = true;

  while(thread_running){
    if(!check_device_connection()) continue;

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
        data = nullptr;
      }

      //Allocate AV frame
      frame = av_frame_alloc();
      if(!frame){
        cout << "[error] ffmpeg - frame memory allocation" << endl;
        data = nullptr;
      }

      //Process or display the video frame here
      int frameFinished;
      result = avcodec_receive_frame(codec_context, frame);
      if(result != 0){
        cout << "[error] ffmpeg - avodec receive frame" << endl;
        data = nullptr;
      }else{
        data = convert_frame_to_data(frame);
        this->frame_width = frame->width;
        this->frame_height = frame->height;
      }

      //Free packet
      av_frame_free(&frame);
      av_packet_unref(packet);
    }
  }

  //---------------------------
}
void Camera::thread_video_device() {
  int currentIndex = 0;
  //---------------------------


  //---------------------------
}
bool Camera::check_device_connection(){
  bool connected = true;
  //---------------------------

  bool device_connected = utl::fct::file::is_device_connected(path_stream);
  if(stream_loaded && stream_active && !device_connected){
    this->clean_video();
    connected = false;
    cout<<"Device disconnected"<<endl;
  }
  else if(!stream_loaded || !stream_active || !device_connected){
    connected = false;
  }

  //---------------------------
  return connected;
}
void Camera::find_camera_devices(){
  // Create a udev context
  struct udev* udev = udev_new();
  if (!udev) {
      std::cerr << "Failed to create udev context" << std::endl;
  }

  // Create a udev enumerator for video devices
  struct udev_enumerate* enumerate = udev_enumerate_new(udev);
  udev_enumerate_add_match_subsystem(enumerate, "video4linux");
  udev_enumerate_scan_devices(enumerate);

  // Get the list of devices
  struct udev_list_entry* devices = udev_enumerate_get_list_entry(enumerate);

  // Iterate through the list and add information to the vector
  struct udev_list_entry* entry;
  udev_list_entry_foreach(entry, devices) {
    const char* path = udev_list_entry_get_name(entry);
    struct udev_device* device = udev_device_new_from_syspath(udev, path);

    const char* deviceNode = udev_device_get_devnode(device);
    const char* deviceName = udev_device_get_sysattr_value(device, "name");

    if (deviceName && deviceNode) {
      // Check if the camera name is already in the list
      auto it = std::find_if(list_camera_devices.begin(), list_camera_devices.end(), [&](const auto& pair) { return pair.first == deviceName; });

      // If not found, add to the list
      if (it == list_camera_devices.end()) {
        list_camera_devices.emplace_back(deviceName, deviceNode);
      }
    }

    udev_device_unref(device);
  }

  // Cleanup
  udev_enumerate_unref(enumerate);
  udev_unref(udev);
}

}
