#include "VK_debug.h"


//Constructor / Destructor
VK_debug::VK_debug(){
  //---------------------------

  //---------------------------
}
VK_debug::~VK_debug(){}

//Main function


//Subfunction
void validation_message(const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData){
  //---------------------------

  // Split the message into individual objects
  std::string message(pCallbackData->pMessage);
  size_t pose_obj_start = message.find("Object ");
  std::string validation_error = message.substr(0, pose_obj_start);

  std::cerr << "--------------------------" << std::endl;
  std::cerr << "[" << "\033[1;32mVL\033[0m] " << validation_error << std::endl;

  // Split the message into individual objects
  while (pose_obj_start != std::string::npos) {
    size_t pose_obj_end = message.find(";", pose_obj_start);
    std::string obj_info = message.substr(pose_obj_start, pose_obj_end - pose_obj_start);

    // Extract handle and type information
    size_t pose_han = obj_info.find("handle = ");
    size_t pose_typ = obj_info.find("type = ");
    std::string object = obj_info.substr(0, pose_han);
    std::string handle = obj_info.substr(pose_han + 9, pose_typ - pose_han - 11);
    std::string type = obj_info.substr(pose_typ + 7);

    // Print type and handle information in shaded colors
    std::cerr << "\033[1;33m" << object << "\033[0m" << std::endl;
    std::cerr << "\033[1;90m" << "type " << "\033[0m" << type << std::endl;
    std::cerr << "\033[1;90m" << "hand " << "\033[0m" << handle << std::endl;

    // Continue searching for more objects
    pose_obj_start = message.find("Object ", pose_obj_end);
  }

  // Extract and print the MessageID and OBJ ERROR
  size_t messageid_start = message.find("MessageID = ");
  size_t messageid_end = message.find(" |", messageid_start);
  std::string messageid_info = message.substr(messageid_start, messageid_end - messageid_start);

  size_t objErrorStart = message.find("OBJ ERROR : ");
  std::string objErrorInfo = message.substr(messageid_end + 3);

  std::cerr << "\033[1;33m" << messageid_info << "\033[0m" << std::endl;
  std::cerr << objErrorInfo << std::endl;

  //---------------------------
}
