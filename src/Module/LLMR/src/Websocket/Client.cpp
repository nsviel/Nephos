#include "Client.h"

#include <iostream>
#include <LLMR/Namespace.h>
#include <Utility/Namespace.h>


namespace net::wsok{

//Constructor / Destructor
Client::Client(llmr::Node* node_llmr){
  //---------------------------

  this->llmr_struct = node_llmr->get_llmr_struct();
  this->llmr_terminal = node_llmr->get_llmr_terminal();

  //---------------------------
}
Client::~Client(){}

//Main function
void Client::start_connection(){
  //---------------------------

  // Create and detach the thread
  this->thread = std::thread(&Client::reconnection_loop, this);
  this->thread.detach();

  //---------------------------
}
void Client::reconnection_loop(){
  //---------------------------

  while (true) {
    // Check if the connection is lost (disconnected)
    if (!llmr_struct->wsok.connection_open) {
      llmr_terminal->add_log("WebSocket connection...", "ok");
      this->setup_client();
      this->setup_connection();
    }

    // Wait for 10 seconds before attempting to reconnect
    std::this_thread::sleep_for(std::chrono::seconds(10));
  }

  //---------------------------
}
void Client::setup_client(){
  if(llmr_struct->wsok.client_setup) return;
  //---------------------------

  client& c = llmr_struct->wsok.c;
  c.set_access_channels(websocketpp::log::alevel::none);
  c.clear_access_channels(websocketpp::log::alevel::frame_payload);
  c.set_error_channels(websocketpp::log::elevel::none);
  c.init_asio();

  // Set up event
  c.set_message_handler(bind(&Client::on_message, this, ::_1, ::_2));
  //c.set_tls_init_handler(bind(&Client::on_tls_init, this, hostname.c_str(), ::_1));
  c.set_open_handler(bind(&Client::on_open, this, ::_1, &c));
  c.set_fail_handler(bind(&Client::on_fail, this, ::_1));
  c.set_close_handler(bind(&Client::on_close, this, ::_1));

  //---------------------------
  llmr_struct->wsok.client_setup = true;
}
void Client::setup_connection(){
  //---------------------------

  try{
    // Create a connection
    client& c = llmr_struct->wsok.c;
    websocketpp::lib::error_code ec;
    client::connection_ptr con = c.get_connection(llmr_struct->wsok.uri, ec);
    if(ec){
      std::cout << "[error] Could not create connection because: " << ec.message() << std::endl;
      return;
    }

    c.connect(con);
    c.run();
  }catch(websocketpp::exception const & e){
    std::cout << "WebSocket Exception: " << e.what() << std::endl;
  }

  //---------------------------
}

//Subfunction
void Client::send_message(std::string message){
  //---------------------------

  if (!llmr_struct->wsok.hdl.lock()) {
    llmr_terminal->add_log("No active connection", "error");
    return;
  }

  // Send the message using the WebSocket connection
  websocketpp::lib::error_code ec;
  client::connection_ptr con = llmr_struct->wsok.c.get_con_from_hdl(llmr_struct->wsok.hdl, ec);
  if (ec) {
    std::cout << "[Error] Failed to get connection pointer: " << ec.message() << std::endl;
    return;
  }

  // Send the message
  llmr_struct->wsok.c.send(con, message, websocketpp::frame::opcode::text);

  //---------------------------
}
void Client::on_open(websocketpp::connection_hdl hdl, client* c){
  //---------------------------

  llmr_terminal->add_log("WebSocket connection opened", "ok");
  llmr_struct->wsok.hdl = hdl;
  llmr_struct->wsok.connection_open = true;

  //---------------------------
}
void Client::on_message(websocketpp::connection_hdl, client::message_ptr msg){
  std::string payload = msg->get_payload();
  //---------------------------

  if(payload == "ping"){
    llmr_struct->wsok.c.send(llmr_struct->wsok.hdl, "pong", websocketpp::frame::opcode::text);
  }else{
    llmr::structure::Item item;
    item.texte = msg->get_payload();
    llmr_struct->terminal.vec_item.push_back(item);
  }

  //---------------------------
}
void Client::on_fail(websocketpp::connection_hdl hdl){
  //---------------------------

  llmr_terminal->add_log("WebSocket connection failed", "error");
  llmr_struct->wsok.connection_open = false;
  llmr_struct->wsok.hdl.reset();

  //---------------------------
}
void Client::on_close(websocketpp::connection_hdl hdl){
  //---------------------------

  llmr_terminal->add_log("WebSocket connection closed", "info");
  llmr_struct->wsok.connection_open = false;
  llmr_struct->wsok.hdl.reset();

  //---------------------------
}
context_ptr Client::on_tls_init(const char * hostname, websocketpp::connection_hdl){
  //---------------------------

  context_ptr ctx = websocketpp::lib::make_shared<boost::asio::ssl::context>(boost::asio::ssl::context::sslv23);
  try {
      ctx->set_options(boost::asio::ssl::context::default_workarounds |
                       boost::asio::ssl::context::no_sslv2 |
                       boost::asio::ssl::context::no_sslv3 |
                       boost::asio::ssl::context::single_dh_use);
  } catch (std::exception& e) {
      std::cout << "TLS Initialization Error: " << e.what() << std::endl;
  }

  //---------------------------
  return ctx;
}

}
