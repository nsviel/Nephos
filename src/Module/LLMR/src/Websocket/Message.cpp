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

  if (message.opcode == websocketpp::frame::opcode::binary) {
    this->manage_binary(message);
  } else {
    this->manage_texte(message);
  }

  //---------------------------
}

//Subfunction
void Message::manage_binary(llmr::structure::Message message){
  //---------------------------

  std::cout << "Received binary data (image)" << std::endl;

  const std::vector<uint8_t>& binary_data = std::get<std::vector<uint8_t>>(message.payload);
  std::ofstream out("received_image.jpg", std::ios::binary);
  out.write(reinterpret_cast<const char*>(binary_data.data()), binary_data.size());
  out.close();

  std::cout << "Image saved as 'received_image.jpg'" << std::endl;

  //---------------------------
}
void Message::manage_texte(llmr::structure::Message message){
  //---------------------------

  llmr::structure::Item item;
  item.texte = std::get<std::string>(message.payload);  // assuming payload is std::string
  llmr_struct->terminal.vec_item.push_back(item);

  //---------------------------
}

}
