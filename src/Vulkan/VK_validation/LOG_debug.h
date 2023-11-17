#ifndef LOG_DEBUG_H
#define LOG_DEBUG_H

#include <UTL_specific/common.h>


class LOG_debug
{
public:
  static LOG_debug& get_instance() {
    static LOG_debug instance;
    return instance;
  }

  //Main function
  void validation_message(const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData);

private:
  LOG_debug() = default;
};


#endif
