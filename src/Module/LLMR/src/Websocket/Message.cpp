#include "Message.h"

#include <iostream>
#include <LLMR/Namespace.h>
#include <Utility/Namespace.h>


namespace llmr::wsok{

//Constructor / Destructor
Message::Message(llmr::Node* node_llmr){
  //---------------------------

  this->llmr_struct = node_llmr->get_llmr_struct();
  this->llmr_terminal = node_llmr->get_llmr_terminal();

  //---------------------------
}
Message::~Message(){}

//Main function
void Message::recv_message(llmr::structure::Message message){
  //---------------------------

  if(message.opcode == websocketpp::frame::opcode::binary){
    std::cout << "Received binary data (image)" << std::endl;

    // Save the received binary data to an image file
    std::ofstream out("received_image.jpg", std::ios::binary);
    out.write(reinterpret_cast<const char*>(msg->get_payload().data()), msg->get_payload().size());
    out.close();

    std::cout << "Image saved as 'received_image.jpg'" << std::endl;
  }else{
    llmr::structure::Item item;
    item.texte = message;
    llmr_struct->terminal.vec_item.push_back(item);
  }

  //---------------------------
}

}
