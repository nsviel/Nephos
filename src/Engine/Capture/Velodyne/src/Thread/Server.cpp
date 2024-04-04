#include "Server.h"

#include <Velodyne/Namespace.h>


namespace vld::thread{

//Constructor / Destructor
Server::Server(vld::structure::Main* vld_struct){
  //---------------------------

  this->vld_struct = vld_struct;
  this->vld_server = new vld::utils::Server();
  this->vld_player = new vld::processing::Player(vld_struct);
  this->vld_frame = new vld::processing::Frame();
  this->vld_vlp16 = new vld::parser::VLP16();

  //---------------------------
}
Server::~Server(){}

//Main function
void Server::start_thread(){
  //---------------------------

  if(!thread_running){
    this->thread = std::thread(&Server::run_thread, this);
  }

  //---------------------------
  this->thread_idle = false;
}
void Server::run_thread(){
  this->thread_running = true;
  //---------------------------

  //First, bind socket server
  vld_server->binding(vld_struct->server.port, vld_struct->server.mtu);
  vld_struct->server.is_listening = true;

  //Data capture loop
  bool is_first_run = true;
  this->thread_running = true;
  while(thread_running){
    //Receive data
    vector<int> packet_dec = vld_server->capture();
    if(packet_dec.size() == 0) continue;

    //Parse decimal packet into point cloud
    utl::file::Entity* data_capture = vld_vlp16->parse_packet(packet_dec);

    //Iteratively build a complete frame
    bool frame_rev = vld_frame->build_frame(data_capture);

    // If frame revolution, make some ope
    if(frame_rev){
      utl::file::Entity* frame = vld_frame->get_endedFrame();
      this->utl_file = *frame;

      //Do not record the first frame
      if(is_first_run == false){
        //this->is_newSubset = true;
      }else{
        is_first_run = false;
      }
    }
  }

  vld_struct->server.is_listening = false;
  vld_server->disconnect();

  //---------------------------
  this->thread_idle = true;
}
void Server::stop_thread(){
  //---------------------------

  this->thread_running = false;
  if(thread.joinable()){
    thread.join();
  }

  //---------------------------
}

//Subfunction


}
