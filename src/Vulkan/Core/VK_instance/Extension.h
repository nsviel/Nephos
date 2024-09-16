#pragma once

namespace vk{class Structure;}


namespace vk::instance{

class Extension
{
public:
  //Constructor / Destructor
  Extension(vk::Structure* vk_struct);
  ~Extension();

public:
  //Main function
  void init();

  //Subfunction
  void extension_instance();
  void extension_window();
  void extension_device();

private:
  vk::Structure* vk_struct;
};

}
