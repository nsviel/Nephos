#pragma once

#include <UTL_specific/common.h>


//Singleton class to store Shader printf output
class LOG_shader
{
public:
  static LOG_shader& get_instance() {
    static LOG_shader instance;
    return instance;
  }
  void add_shader_printf(const std::string& message) {
    shader_printf = message;
  }
  const std::string& get_shader_printf() const {
    return shader_printf;
  }

private:
  LOG_shader() = default;
  std::string shader_printf;
};
