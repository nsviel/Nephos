#pragma once

#include <Application/Node.h>
#include <thread>

namespace app{class Node;}


class App
{
public:
  //Constructor / Destructor
  App();
  ~App();

public:
  void run();
  void close();
  void add_cloud();


private:
  app::Node node_app;

  std::thread thread;
};
