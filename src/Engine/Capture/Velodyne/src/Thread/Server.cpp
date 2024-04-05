#include "Server.h"

#include <Velodyne/Namespace.h>
#include <Scene/Namespace.h>


namespace vld::thread{

//Constructor / Destructor
Server::Server(vld::Node* node_vld){
  //---------------------------

  eng::scene::Node* node_scene = node_vld->get_node_scene();

  this->sce_database = node_scene->get_scene_database();
  this->sce_loader = node_scene->get_scene_loader();
  this->sce_set = new eng::scene::Set();

  this->vld_struct = node_vld->get_vld_struct();
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
  vector<int> packet_dec = vld_server->capture();
  if(packet_dec.size() == 0) return;

  //Parse decimal packet into point cloud
  utl::file::Data* data = vld_vlp16->parse_packet(packet_dec);

  //Iteratively build a complete frame
  bool frame_rev = vld_frame->build_frame(data);

  // If frame revolution, make some ope
  if(frame_rev){
    utl::file::Data* data = vld_frame->get_endedFrame();
    this->create_object(data);
  }

  //---------------------------
}

std::mutex creationMutex;
void Server::create_object(utl::file::Data* data){
  //---------------------------

static int a = 0;
  utl::type::Set* set_scene = sce_database->get_set_scene();
  utl::type::Set* set_capture = sce_set->get_or_create_subset(set_scene, "Capture");

if(a < 2){say("---");
  sce_set->remove_entity_all(set_capture);sayHello();
  utl::entity::Object* object = sce_loader->create_object(data);sayHello();
  sce_set->insert_entity(set_capture, object);
  sayHello();
}

a++;


  //std::this_thread::sleep_for(std::chrono::milliseconds(60));

/*
  //Cloud* new_subset = extractManager->extract_data(udp_capture);
  //this->operation_new_subset(new_subset);
  //Set new cloud identifieurs
  cloud->name = "frame_" + to_string(collection_capture->ID_obj_last);
  cloud->ID = collection_capture->ID_obj_last;
  cloud->draw_point_size = point_size;
  collection_capture->ID_obj_last++;

  //Update cloud data
  sceneManager->update_buffer_location(cloud);

  //Insert the cloud inside the capture cloud
  collection_capture->obj_add_new(cloud);

  //Control object visibilities
  visibilityManager->compute_visibility(collection, ID_object);

  //Colorization
  colorManager->make_colorization(collection, ID_object);
*/
  //---------------------------
}


}
