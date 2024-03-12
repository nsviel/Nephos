#include "Operation.h"

#include <K4N/Namespace.h>
#include <Operation/Namespace.h>


namespace k4n::utils{

//Constructor / Destructor
Operation::Operation(){
  //---------------------------


  //---------------------------
}
Operation::~Operation(){}

//Data operation
void Operation::make_normal_from_depth_image(k4n::dev::Sensor* sensor){
  uint8_t* depth = sensor->depth.data.buffer;
  //---------------------------

  utl::type::Data* data = sensor->get_data();

  int width = sensor->depth.data.width;
  int height = sensor->depth.data.height;
  vector<vec3> Nxyz;

 //BUT OBTENIR UNE NORMAL IMAGE FROM DEPTH IMAGE

  for(int i=0; i<height; i++){
    for(int j=0; j<width; j++){

      int id_1 = i * width + j + 1;
      int id_2 = i * width + j - 1;
      uint16_t value_1 = depth[id_1 * 2] | (depth[id_1 * 2 + 1] << 8);
      uint16_t value_2 = depth[id_2 * 2] | (depth[id_2 * 2 + 1] << 8);
      float dzdx = (value_1 - value_2) / 2.0;

      id_1 = (i + 1) * width + j;
      id_2 = (i - 1) * width + j;
      value_1 = depth[id_1 * 2] | (depth[id_1 * 2 + 1] << 8);
      value_2 = depth[id_2 * 2] | (depth[id_2 * 2 + 1] << 8);
      float dzdy = (value_1 - value_2) / 2.0;

      vec3 d(-dzdx, -dzdy, 1.0f);
      vec3 n = glm::normalize(d);

      Nxyz.push_back(n);
    }
  }

data->Nxyz = Nxyz;

/*
  for(int x = 0; x < depth.rows; ++x)
  {
      for(int y = 0; y < depth.cols; ++y)
      {

          float dzdx = (depth.at<float>(x+1, y) - depth.at<float>(x-1, y)) / 2.0;
          float dzdy = (depth.at<float>(x, y+1) - depth.at<float>(x, y-1)) / 2.0;

          Vec3f d(-dzdx, -dzdy, 1.0f);
          Vec3f n = normalize(d);

          normals.at<Vec3f>(x, y) = n;
      }
  }

  imshow("depth", depth / 255);
  imshow("normals", normals);
*/
  //---------------------------
}
void Operation::make_cloud_export(k4n::dev::Sensor* sensor){
  string& path_dir = sensor->master->operation.export_path_dir;
  //---------------------------

  //Check if directory exists, if not create it
  if(!utl::fct::directory::is_dir_exist(path_dir)){
    utl::fct::directory::create_new(path_dir);
  }



  //---------------------------
}

//Player operation
float Operation::find_mkv_ts_beg(string path){
  //---------------------------

  k4a::playback playback = k4a::playback::open(path.c_str());;
  playback.seek_timestamp(std::chrono::microseconds(0), K4A_PLAYBACK_SEEK_BEGIN);

  k4a::capture capture;
  k4a::image color = nullptr;
  while(color == nullptr){
    playback.get_next_capture(&capture);
    color = capture.get_color_image();
  }

  float ts_beg = color.get_device_timestamp().count() / 1000000.0f;

  //---------------------------
  return ts_beg;
}
float Operation::find_mkv_ts_end(string path){
  //---------------------------

  k4a::playback playback = k4a::playback::open(path.c_str());;
  playback.seek_timestamp(std::chrono::microseconds(0), K4A_PLAYBACK_SEEK_END);

  k4a::capture capture;
  k4a::image color = nullptr;
  while(color == nullptr){
    playback.get_previous_capture(&capture);
    color = capture.get_color_image();
  }

  float ts_end = color.get_device_timestamp().count() / 1000000.0f;

  //---------------------------
  return ts_end;
}

}
