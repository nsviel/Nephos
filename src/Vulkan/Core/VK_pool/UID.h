#pragma once

namespace vk{class Structure;}


namespace vk::instance{

class UID
{
public:
  //Constructor / Destructor
  UID(vk::Structure* vk_struct);
  ~UID();

public:
  //Main function
  int query_free_UID();

private:
  vk::Structure* vk_struct;
};

}
