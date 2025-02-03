#pragma once

#include <string>

namespace llmr{class Node;}
namespace net::wsok{class Client;}


namespace llmr{

class Interface
{
public:
  //Constructor / Destructor
  Interface(llmr::Node* node_llmr);
  ~Interface();

public:
  //Main function
  void init();
  void send_llm_message(std::string message);

private:
  net::wsok::Client* llmr_wsok;
};

}
