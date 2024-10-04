#pragma once

namespace vk{class Structure;}


namespace vk::command{

class Queue
{
public:
  //Constructor / Destructor
  Queue(vk::Structure* vk_struct);
  ~Queue();

public:
  //Main function
  void init();
  void clean();

private:
  vk::Structure* vk_struct;
};

}
