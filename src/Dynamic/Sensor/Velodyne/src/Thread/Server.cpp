#include "Server.h"

#include <Velodyne/Namespace.h>
#include <Core/Namespace.h>
#include <IO/Namespace.h>
#include <Utility/Namespace.h>
#include <Element/Namespace.h>
#include <Importer/Namespace.h>
#include <Graph/Namespace.h>


namespace vld::thread{

//Constructor / Destructor
Server::Server(vld::Node* node_vld){
  //---------------------------

  eng::Node* node_engine = node_vld->get_node_engine();
  dat::Node* node_data = node_engine->get_node_data();
  io::Node* node_io = node_engine->get_node_io();
  dat::graph::Node* node_graph = node_data->get_node_graph();
  io::imp::Node* node_importer = node_io->get_node_importer();

  this->dat_graph = node_graph->get_dat_graph();
  this->io_loader = node_importer->get_io_importer();
  this->dat_set = node_data->get_dat_set();

  this->vld_struct = node_vld->get_vld_struct();
  this->vld_server = new vld::utils::Server();
  this->vld_player = new vld::processing::Player(vld_struct);
  this->vld_frame = new vld::processing::Frame();
  this->vld_vlp16 = new vld::parser::VLP16();
  this->vld_data = new vld::main::Data(node_vld);
  this->thread_screenshot = new vld::thread::Screenshot(node_vld);

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
  bool binded = vld_server->binding(vld_struct->server.port, vld_struct->server.mtu);
  if(!binded) return;
  vld_struct->server.is_listening = true;

  //Data capture loop
  this->thread_running = true;
  while(thread_running){
    this->capture_data();
  }

  vld_struct->server.is_listening = false;
  vld_server->disconnect();

  //---------------------------
  this->thread_idle = true;
}
void Server::stop_thread(){
  //---------------------------

  thread_screenshot->stop_thread();
  this->thread_running = false;
  if(thread.joinable()){
    thread.join();
  }

  //---------------------------
}

//Subfunction
void Server::capture_data(){
  //---------------------------

  //Receive data
  std::vector<int> packet_dec = vld_server->capture();
  if(packet_dec.size() == 0) return;
  vld_data->create_object();
  thread_screenshot->start_thread();

  //Parse decimal packet into point cloud
  utl::base::Data* data = vld_vlp16->parse_packet(packet_dec);

  //Iteratively build a complete frame
  bool frame_rev = vld_frame->build_frame(data);

  // If frame revolution, make some ope
  if(frame_rev){
    utl::base::Data* data = vld_frame->get_endedFrame();
    this->update_object(data);
  }

  //---------------------------
}
void Server::update_object(utl::base::Data* data){
  //---------------------------

  std::string name = "capture_" + std::to_string(vld_struct->data.current_frame_ID++);
  dat::base::Object* object = vld_struct->data.object;
  object->name = name;
  object->data.name = name + "::data";
  object->data.size = data->xyz.size();
  //object->data.topology.type = data->topology;

  object->data.xyz = data->xyz;
  object->data.rgb = data->rgb;
  object->data.uv = data->uv;

  //If no color, fill it with white
  if(object->data.rgb.size() == 0){
    for(int i=0; i<data->xyz.size(); i++){
      object->data.rgb.push_back(glm::vec4(1,1,1,1));
    }
  }

  //object->update_data();
  //object->update_glyph();

  //---------------------------
}


}
