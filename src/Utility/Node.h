#pragma once

#include <Utility/Specific/common.h>

class Config;
namespace utl::element{class Window;}
namespace utl::element{class Profiler;}


namespace utl{

class Node : public utl::type::Node
{
public:
  //Constructor / Destructor
  Node(Config* config, utl::element::Profiler* cpu_profiler);
  ~Node();

public:
  //Main function
  void init();
  void loop();
  void gui();
  void exit();

  inline utl::element::Window* get_utl_window(){return utl_window;}
  inline utl::element::Profiler* get_cpu_profiler(){return cpu_profiler;}

private:
  utl::element::Window* utl_window;
  utl::element::Profiler* cpu_profiler;
};

}
