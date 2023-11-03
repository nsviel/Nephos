#ifndef VK_ENGINE_H
#define VK_ENGINE_H

#include "VK_struct/typedef.h"
#include <ELE_specific/common.h>

class Engine;
class Window;
class FPS_counter;
class Struct_param;

class Struct_vulkan;
class VK_surface;
class VK_instance;
class VK_device;
class VK_swapchain;
class VK_renderpass;
class VK_pipeline;
class VK_command;
class VK_cmd;
class VK_synchronization;
class VK_submit;
class VK_buffer;
class VK_descriptor;
class VK_uniform;
class VK_texture;
class VK_depth;
class VK_data;
class VK_viewport;
class VK_shader;
class VK_reload;
class VK_physical_device;
class VK_frame;
class VK_canvas;
class VK_color;
class VK_binding;
class VK_image;
class VK_drawing;
class VK_command_buffer;


class VK_engine
{
public:
  //Constructor / Destructor
  VK_engine(Engine* engine);
  ~VK_engine();

public:
  //Main functions
  void init();
  void clean();
  void loop_draw_frame();
  void device_wait_idle();

  inline Engine* get_engine(){return engine;}
  inline Window* get_window(){return window;}

  inline Struct_param* get_param(){return struct_param;}
  inline Struct_vulkan* get_struct_vulkan(){return struct_vulkan;}

  inline VK_device* get_vk_device(){return vk_device;}
  inline VK_surface* get_vk_surface(){return vk_surface;}
  inline VK_swapchain* get_vk_swapchain(){return vk_swapchain;}
  inline VK_synchronization* get_vk_synchronization(){return vk_synchronization;}
  inline VK_command* get_vk_command(){return vk_command;}
  inline VK_cmd* get_vk_cmd(){return vk_cmd;}
  inline VK_instance* get_vk_instance(){return vk_instance;}
  inline VK_renderpass* get_vk_renderpass(){return vk_renderpass;}
  inline VK_pipeline* get_vk_pipeline(){return vk_pipeline;}
  inline VK_buffer* get_vk_buffer(){return vk_buffer;}
  inline VK_descriptor* get_vk_descriptor(){return vk_descriptor;}
  inline VK_texture* get_vk_texture(){return vk_texture;}
  inline VK_depth* get_vk_depth(){return vk_depth;}
  inline VK_color* get_vk_color(){return vk_color;}
  inline VK_data* get_vk_data(){return vk_data;}
  inline VK_viewport* get_vk_viewport(){return vk_viewport;}
  inline VK_shader* get_vk_shader(){return vk_shader;}
  inline VK_reload* get_vk_reload(){return vk_reload;}
  inline VK_physical_device* get_vk_physical_device(){return vk_physical_device;}
  inline VK_frame* get_vk_frame(){return vk_frame;}
  inline VK_submit* get_vk_submit(){return vk_submit;}
  inline VK_canvas* get_vk_canvas(){return vk_canvas;}
  inline VK_binding* get_vk_binding(){return vk_binding;}
  inline VK_image* get_vk_image(){return vk_image;}
  inline VK_drawing* get_vk_drawing(){return vk_drawing;}
  inline VK_uniform* get_vk_uniform(){return vk_uniform;}
  inline VK_command_buffer* get_vk_command_buffer(){return vk_command_buffer;}

private:
  Engine* engine;
  Struct_param* struct_param;
  Window* window;
  Timer timer;
  FPS_counter* fps_counter;

  Struct_vulkan* struct_vulkan;
  VK_surface* vk_surface;
  VK_instance* vk_instance;
  VK_command_buffer* vk_command_buffer;
  VK_device* vk_device;
  VK_swapchain* vk_swapchain;
  VK_renderpass* vk_renderpass;
  VK_pipeline* vk_pipeline;
  VK_uniform* vk_uniform;
  VK_image* vk_image;
  VK_command* vk_command;
  VK_cmd* vk_cmd;
  VK_binding* vk_binding;
  VK_synchronization* vk_synchronization;
  VK_submit* vk_submit;
  VK_buffer* vk_buffer;
  VK_descriptor* vk_descriptor;
  VK_depth* vk_depth;
  VK_texture* vk_texture;
  VK_data* vk_data;
  VK_viewport* vk_viewport;
  VK_shader* vk_shader;
  VK_reload* vk_reload;
  VK_physical_device* vk_physical_device;
  VK_frame* vk_frame;
  VK_canvas* vk_canvas;
  VK_color* vk_color;
  VK_drawing* vk_drawing;
};

#endif
