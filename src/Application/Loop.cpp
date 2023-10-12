#include "Loop.h"
#include "../config.h"

#include <GUI.h>
#include <Engine.h>
#include <GPU/GPU_render.h>
#include <Vulkan/VK_engine.h>
#include <Camera/Camera.h>
#include <Window/Window.h>
#include <iostream>


//Constructor / Destructor
Loop::Loop(){
  //---------------------------

  this->window = new Window();
  this->engine = new Engine(window);
  this->gui = new GUI(engine);




/*

  string truc = "Validation Error: [ VUID-VkDescriptorSetAllocateInfo-descriptorPool-00307 ] Object 0: handle = 0xc5a188000000011d, type = VK_OBJECT_TYPE_DESCRIPTOR_POOL; | MessageID = 0x21859338 | vkAllocateDescriptorSets(): Unable to allocate 1 descriptors of type VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER from VkDescriptorPool 0xc5a188000000011d[]. This pool only has 0 descriptors of this type remaining. The Vulkan spec states: descriptorPool must have enough free descriptor capacity remaining to allocate the descriptor sets of the specified layouts (https://vulkan.lunarg.com/doc/view/1.3.243.0/linux/1.3-extensions/vkspec.html#VUID-VkDescriptorSetAllocateInfo-descriptorPool-00307)";
say(truc);
say("");

  std::string message(truc);
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
    std::string handle = obj_info.substr(pose_han + 9, pose_typ - pose_han - 9);
    std::string type = obj_info.substr(pose_typ + 7);

    // Print type and handle information in shaded colors
    std::cerr << "\033[1;34m" << object << "\033[0m" << std::endl;
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

  std::cerr << "\033[1;34m" << messageid_info << "\033[0m" << std::endl;
  std::cerr << objErrorInfo << std::endl;

exit(0);
*/



  //---------------------------
}
Loop::~Loop(){}

//Main function
void Loop::run(){
  //---------------------------

  this->init();
  this->loop();
  this->end();

  //---------------------------
}

//Subfunction
void Loop::init(){
  Config config;
  //---------------------------

  window->create_window(config.window_dim.x, config.window_dim.y, config.window_title);
  engine->init();
  gui->init();

  //---------------------------
}
void Loop::loop(){
  //---------------------------

  auto start_time = std::chrono::steady_clock::now();
  while(!window->window_should_close()){
    window->manage_input();
    gui->loop();
    engine->loop();
  }
  engine->wait_for_gpu_idle();

  //---------------------------
}
void Loop::end(){
  //---------------------------

  gui->exit();
  engine->exit();
  window->destroy_window();

  //---------------------------
}
