#pragma once

#include <LLMR/src/Structure/Websocket.h>
#include <memory>
#include <string>
#include <thread>

namespace llmr{class Node;}
namespace llmr{class Structure;}
namespace llmr{class Terminal;}


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
  void reconnection_loop();
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
};

}
