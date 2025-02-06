#pragma once

#include <websocketpp/config/asio_client.hpp>
#include <websocketpp/client.hpp>
#include <memory>
#include <string>
#include <thread>

namespace llmr{class Node;}
namespace llmr{class Structure;}
namespace llmr{class Terminal;}

typedef websocketpp::client<websocketpp::config::asio_client> client;
typedef websocketpp::lib::shared_ptr<websocketpp::lib::asio::ssl::context> context_ptr;

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;


namespace net::wsok{

class Client
{
public:
  //Constructor / Destructor
  Client(llmr::Node* node_llmr);
  ~Client();

public:
  //Main function
  void start_connection();
  void setup_connection();

  //Subfunction
  void send_message(std::string message);
  void on_open(websocketpp::connection_hdl hdl, client* c);
  void on_message(websocketpp::connection_hdl hdl, client::message_ptr msg);
  void on_fail(websocketpp::connection_hdl hdl);
  void on_close(websocketpp::connection_hdl hdl);
  context_ptr on_tls_init(const char * hostname, websocketpp::connection_hdl);

private:
  llmr::Structure* llmr_struct;
  llmr::Terminal* llmr_terminal;

  std::thread thread;
  client c;
  websocketpp::connection_hdl hdl;
};

}
