#pragma once
/*
#include <websocketpp/config/asio_client.hpp>
#include <websocketpp/client.hpp>
#include <memory>
#include <string>

typedef websocketpp::client<websocketpp::config::asio_tls_client> client;
typedef websocketpp::lib::shared_ptr<websocketpp::lib::asio::ssl::context> context_ptr;

namespace net::wsok{

class Client
{
public:
  //Constructor / Destructor
  Client();
  ~Client();

public:
  //Main function
  void on_open(websocketpp::connection_hdl hdl, client* c);
  void on_message(websocketpp::connection_hdl, client::message_ptr msg);
  void on_fail(websocketpp::connection_hdl hdl);
  void on_close(websocketpp::connection_hdl hdl);
  context_ptr on_tls_init(const char * hostname, websocketpp::connection_hdl);

private:

};

}
*/
