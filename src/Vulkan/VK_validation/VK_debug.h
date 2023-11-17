#ifndef VK_DEBUG_H
#define VK_DEBUG_H

#include <UTL_specific/common.h>




class VK_debug
{
public:
  //Constructor / Destructor
  VK_debug();
  ~VK_debug();

public:
  //Main functions
  void validation_message(const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData);

private:

};

#endif
