#include "Client.h"

#include <iostream>
#include <Utility/Namespace.h>


namespace net::wsok{

//Constructor / Destructor
Client::Client(){
  //---------------------------

  //---------------------------
}
Client::~Client(){}

//Main function
void Client::start_connection(){
  //---------------------------

  // Create and detach the thread
  this->thread = std::thread(&Client::setup_connection, this);
  this->thread.detach();

  //---------------------------
}
void Client::setup_connection(){
  //---------------------------

  std::string hostname = "localhost:8765";
  std::string uri = "ws://" + hostname;

  try {
    //initialize WebSocket
    c.set_access_channels(websocketpp::log::alevel::all);
    c.clear_access_channels(websocketpp::log::alevel::frame_payload);
    c.set_error_channels(websocketpp::log::elevel::all);
    c.init_asio();

    // Set up event
    c.set_message_handler(bind(&Client::on_message, this, ::_1, ::_2));
    //c.set_tls_init_handler(bind(&Client::on_tls_init, this, hostname.c_str(), ::_1));
    c.set_open_handler(bind(&Client::on_open, this, ::_1, &c));
    c.set_fail_handler(bind(&Client::on_fail, this, ::_1));
    c.set_close_handler(bind(&Client::on_close, this, ::_1));

    // Create a connection
    websocketpp::lib::error_code ec;
    client::connection_ptr con = c.get_connection(uri, ec);
    if(ec){
      std::cout << "Could not create connection because: " << ec.message() << std::endl;
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

  if (!hdl.lock()) {
    std::cout << "[Error] No active connection!" << std::endl;
    return;
  }

  // Send the message using the WebSocket connection
  websocketpp::lib::error_code ec;
  client::connection_ptr con = c.get_con_from_hdl(hdl, ec);
  if (ec) {
    std::cout << "[Error] Failed to get connection pointer: " << ec.message() << std::endl;
    return;
  }

  // Send the message
  c.send(con, message, websocketpp::frame::opcode::text);

  //---------------------------
}
void Client::on_open(websocketpp::connection_hdl hdl, client* c){
  //---------------------------

  std::cout << "[OK] WebSocket connection opened" << std::endl;
  this->hdl = hdl;

  //---------------------------
}
void Client::on_message(websocketpp::connection_hdl, client::message_ptr msg){
  //---------------------------

  std::cout << "Received message: " << msg->get_payload() << std::endl;

  //---------------------------
}
void Client::on_fail(websocketpp::connection_hdl hdl){
  //---------------------------

  std::cout << "WebSocket connection failed!" << std::endl;

  //---------------------------
}
void Client::on_close(websocketpp::connection_hdl hdl){
  //---------------------------

  std::cout << "WebSocket connection closed!" << std::endl;

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
