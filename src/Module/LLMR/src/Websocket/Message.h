#pragma once

#include <LLMR/src/Structure/Websocket.h>
#include <memory>
#include <string>
#include <thread>

namespace llmr{class Node;}
namespace llmr{class Structure;}
namespace llmr{class Terminal;}
namespace llmr::structure{class Message;}


namespace llmr::wsok{

class Message
{
public:
  //Constructor / Destructor
  Message(llmr::Node* node_llmr);
  ~Message();

public:
  //Main function
  void recv_message(llmr::structure::Message message);

private:
  llmr::Structure* llmr_struct;
  llmr::Terminal* llmr_terminal;

  std::thread thread;
};

}
