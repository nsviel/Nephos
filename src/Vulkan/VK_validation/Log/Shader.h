#pragma once

#include <string>


namespace vk::validation::log{

//Singleton class to store Shader printf output
class Shader
{
public:
  static Shader& get_instance(){
    static Shader instance;
    return instance;
  }
  void add_shader_printf(const std::string& message){
    shader_printf = message;
  }
  const std::string& get_shader_printf() const {
    return shader_printf;
  }

private:
  Shader() = default;
  std::string shader_printf;
};

}
