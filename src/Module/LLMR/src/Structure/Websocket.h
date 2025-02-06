#pragma once

#include <websocketpp/config/asio_client.hpp>
#include <websocketpp/client.hpp>
#include <vector>
#include <string>

typedef websocketpp::client<websocketpp::config::asio_client> client;
typedef websocketpp::lib::shared_ptr<websocketpp::lib::asio::ssl::context> context_ptr;

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;


namespace llmr::structure{

struct Websocket{
  //---------------------------

  //ID
  std::string hostname = "localhost:8765";
  std::string uri = "ws://" + hostname;

  //Parameter
  websocketpp::connection_hdl hdl;
  websocketpp::client<websocketpp::config::asio_client> c;
  bool connection_open = false;

  //---------------------------
};

}
