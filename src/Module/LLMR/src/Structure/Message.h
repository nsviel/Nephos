#pragma once

#include <LLMR/src/Structure/Terminal.h>
#include <LLMR/src/Structure/Websocket.h>
#include <variant>
#include <vector>
#include <string>

namespace llmr::structure{

struct Message{
  //---------------------------

  std::chrono::system_clock::time_point timestamp;
  websocketpp::frame::opcode::value opcode;
  std::variant<std::string, std::vector<uint8_t>> payload;
  std::string remote_endpoint;
  std::string wsok_version;
  size_t size;
  bool ended;

  //---------------------------
};

}
