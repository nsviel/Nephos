#include "Terminal.h"

#include <LLMR/Namespace.h>
#include <Utility/Namespace.h>


namespace llmr{

//Constructor / Destructor
Terminal::Terminal(llmr::Node* node_llmr){
  //---------------------------

  this->llmr_struct = node_llmr->get_llmr_struct();
  
  //---------------------------
}
Terminal::~Terminal(){}

//Main function
void Terminal::add_log(std::string log, std::string prefix = ""){
  //---------------------------

  //Prefix
  glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
  if(prefix != "")
  if(prefix == "#") color = glm::vec4(1.0f, 0.8f, 0.6f, 1.0f);
  else if(prefix == "error") color = glm::vec4(1.0f, 0.4f, 0.4f, 1.0f);
  else if(prefix == "\\o/") color = glm::vec4(0.4f, 1.0f, 0.4f, 1.0f);

  //Item
  llmr::structure::Item item;
  item.prefix = prefix;
  item.texte = log;
  item.color = color;
  llmr_struct->terminal.vec_item.push_back(item);

  //---------------------------
}
void Terminal::clear_log(){
  //---------------------------

  llmr_struct->terminal.vec_item.clear();

  //---------------------------
}

}
