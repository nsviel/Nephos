#include "Client.h"

#include <iostream>
#include <LLMR/Namespace.h>
#include <Utility/Namespace.h>
#include <nlohmann/json.hpp>


namespace llmr::wsok{

//Constructor / Destructor
Client::Client(llmr::Node* node_llmr){
  //---------------------------

  this->llmr_struct = node_llmr->get_llmr_struct();
  this->llmr_terminal = node_llmr->get_llmr_terminal();
  this->wsok_message = new llmr::wsok::Message(node_llmr);

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

  while(true){
    // Check if the connection is lost (disconnected)
    if(!llmr_struct->wsok.connection_open){
      this->setup_client();
      this->setup_connection();
    }

    // Wait for 10 seconds before attempting to reconnect
    std::this_thread::sleep_for(std::chrono::seconds(10));
  }

  //---------------------------
}

//Socket
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
void Client::close_connection(){
  //---------------------------

  llmr_struct->wsok.c.close(llmr_struct->wsok.hdl, websocketpp::close::status::normal, "");
  llmr_struct->wsok.connection_open = false;
  llmr_struct->wsok.hdl.reset();

  //---------------------------
}

//Subfunction
void Client::send_message(std::string command, std::string message){
  if(!llmr_struct->wsok.connection_open) return;
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

  // Create a JSON object with command and message
  nlohmann::json j;
  j["command"] = command;
  j["message"] = message;

  // Serialize the JSON object into a string
  std::string json_str = j.dump();  // Converts the JSON object to a string

  // Send the serialized JSON string
  llmr_struct->wsok.c.send(con, json_str, websocketpp::frame::opcode::text);

  //---------------------------
}
void Client::on_open(websocketpp::connection_hdl hdl, client* c){
  //---------------------------

  llmr_terminal->add_log("Connection opened", "ok");
  llmr_struct->wsok.hdl = hdl;
  llmr_struct->wsok.connection_open = true;
  this->send_message("get", "library");

  //---------------------------
}
void Client::on_message(websocketpp::connection_hdl, client::message_ptr msg){
  //---------------------------

  if(msg->get_payload() == "ping"){
    llmr_struct->wsok.c.send(llmr_struct->wsok.hdl, "pong", websocketpp::frame::opcode::text);
  }else{
    llmr::structure::Message message;
    message.size = msg->get_payload().size();
    message.opcode = msg->get_opcode();
    if(message.opcode == websocketpp::frame::opcode::binary){
      message.payload = std::vector<uint8_t>(msg->get_payload().begin(), msg->get_payload().end());
    }
    else if(message.opcode == websocketpp::frame::opcode::text){
      message.payload = msg->get_payload();
    }
    wsok_message->recv_message(message);
  }

  //---------------------------
}
void Client::on_fail(websocketpp::connection_hdl hdl){
  //---------------------------

  llmr_terminal->add_log("Connection failed", "error");
  this->close_connection();

  //---------------------------
}
void Client::on_close(websocketpp::connection_hdl hdl){
  //---------------------------

  llmr_terminal->add_log("Connection closed", "info");
  this->close_connection();

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
