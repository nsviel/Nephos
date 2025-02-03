#include "Interface.h"

#include <LLMR/Namespace.h>
#include <Utility/Namespace.h>


namespace llmr{

//Constructor / Destructor
Interface::Interface(llmr::Node* node_llmr){
  //---------------------------

  this->llmr_wsok = new net::wsok::Client(node_llmr);

  //---------------------------
}
Interface::~Interface(){}

//Main function
void Interface::init(){
  //---------------------------

  llmr_wsok->start_connection();

  //---------------------------
}
void Interface::send_llm_message(std::string message){
  //---------------------------

  llmr_wsok->send_message(message);

  //---------------------------
}

}
