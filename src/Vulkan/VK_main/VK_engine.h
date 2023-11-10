#ifndef VK_ENGINE_H
#define VK_ENGINE_H

#include <VK_struct/typedef.h>
#include <VK_struct/Struct_data.h>
#include <VK_main/Struct_vulkan.h>
#include <ELE_specific/common.h>

class ELE_window;
class Struct_vulkan;
class VK_surface;
class VK_instance;
class VK_device;
class VK_swapchain;
class VK_renderpass;
class VK_descriptor;
class VK_texture;
class VK_data;
class VK_viewport;
class VK_reload;
class VK_frame;
class VK_canvas;
class VK_command_buffer;


class VK_engine
{
public:
  //Constructor / Destructor
  VK_engine(ELE_window* ele_window);
  ~VK_engine();

public:
  //Main functions
  void init();
  void loop();
  void clean();
  void device_wait_idle();
  void reload_shader(string shader, string subshader);

  //Data function
  void insert_object_in_engine(Object* object);
  void remove_object_in_engine(Object* object);

  inline Struct_vulkan* get_struct_vulkan(){return struct_vulkan;}

  inline Struct_renderpass* get_renderpass(int i){return struct_vulkan->render.vec_renderpass[i];}
  inline std::list<Struct_data*> get_list_data(){return struct_vulkan->list_object;}
  inline void set_ele_window(ELE_window* value){this->ele_window = value;}

private:
  ELE_window* ele_window;

  Struct_synchro* struct_synchro;
  Struct_vulkan* struct_vulkan;

  VK_surface* vk_surface;
  VK_instance* vk_instance;
  VK_command_buffer* vk_command_buffer;
  VK_device* vk_device;
  VK_swapchain* vk_swapchain;
  VK_renderpass* vk_renderpass;
  VK_descriptor* vk_descriptor;
  VK_texture* vk_texture;
  VK_data* vk_data;
  VK_viewport* vk_viewport;
  VK_reload* vk_reload;
  VK_frame* vk_frame;
  VK_canvas* vk_canvas;

  Timer timer;
};

#endif
