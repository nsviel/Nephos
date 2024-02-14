#include "Capture.h"

#include <Engine/Capture/Velodyne/Namespace.h>

#include <jsoncpp/json/value.h>
#include <jsoncpp/json/json.h>
#include <unistd.h>
#include <fstream>
#include <curl/curl.h>
#include <chrono>

using namespace std::chrono;


namespace velodyne{

//Constructor / Destructor
Capture::Capture(){
  //---------------------------

  this->velo_server = new velodyne::Server();
  this->velo_frame = new velodyne::Frame();
  this->parser_vlp16 = new velodyne::parser::VLP16();

  this->lidar_ip = "192.168.1.201";
  this->thread_running = false;

  //---------------------------
}
Capture::~Capture(){}

//Main function
void Capture::start_thread(int port){
  //---------------------------

  this->thread = std::thread(&Capture::run_thread, this, port);

  //---------------------------
}
void Capture::run_thread(int port){
  //---------------------------

  bool is_first_run = true;
  int size_max = 1248;

  velo_server->binding(port, size_max);

  this->thread_running = true;
  while(thread_running){
    vector<int> packet_dec = velo_server->capture();

    //Parse decimal packet into point cloud
    if(packet_dec.size() != 0){
      utl::media::File* data_cap = parser_vlp16->parse_packet(packet_dec);

      //Iteratively build a complete frame
      bool frame_rev = velo_frame->build_frame(data_cap);

      // If frame revolution, make some ope
      if(frame_rev){
        utl::media::File* frame = velo_frame->get_endedFrame();
        this->utl_file = *frame;

        //Do not record the first frame
        if(is_first_run == false){
          //this->is_newSubset = true;
        }else{
          is_first_run = false;
        }
      }
    }
  }

  velo_server->disconnect();

  //---------------------------
}
void Capture::stop_thread(){
  //---------------------------

  this->thread_running = false;
  if(thread.joinable()){
    thread.join();
  }

  //---------------------------
}

}
