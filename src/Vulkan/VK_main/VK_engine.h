#ifndef VK_ENGINE_H
#define VK_ENGINE_H

#include "VK_struct/typedef.h"
#include "VK_struct/struct_data.h"
#include "VK_struct/struct_vulkan.h"
#include <ELE_specific/common.h>

class Engine;
class Window;
class Struct_param;
class Struct_synchro;
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
class VK_physical_device;
class VK_frame;
class VK_canvas;
class VK_drawing;
class VK_command_buffer;
class VK_imgui;
class VK_render;


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
  void device_wait_idle();
  void reload_shader(string shader, string subshader);

  //Data function
  void insert_object_in_engine(Object* object);
  void insert_glyph_in_engine(Object* object);
  void remove_object_in_engine(Object* object);

  inline Engine* get_engine(){return engine;}
  inline Window* get_window(){return window;}

  inline Struct_param* get_struct_param(){return struct_param;}
  inline Struct_vulkan* get_struct_vulkan(){return struct_vulkan;}
  inline Struct_synchro* get_struct_synchro(){return struct_synchro;}

  inline VK_render* get_vk_render(){return vk_render;}
  inline VK_device* get_vk_device(){return vk_device;}
  inline VK_surface* get_vk_surface(){return vk_surface;}
  inline VK_swapchain* get_vk_swapchain(){return vk_swapchain;}
  inline VK_instance* get_vk_instance(){return vk_instance;}
  inline VK_renderpass* get_vk_renderpass(){return vk_renderpass;}
  inline VK_descriptor* get_vk_descriptor(){return vk_descriptor;}
  inline VK_texture* get_vk_texture(){return vk_texture;}
  inline VK_data* get_vk_data(){return vk_data;}
  inline VK_viewport* get_vk_viewport(){return vk_viewport;}
  inline VK_reload* get_vk_reload(){return vk_reload;}
  inline VK_frame* get_vk_frame(){return vk_frame;}
  inline VK_canvas* get_vk_canvas(){return vk_canvas;}
  inline VK_drawing* get_vk_drawing(){return vk_drawing;}
  inline VK_command_buffer* get_vk_command_buffer(){return vk_command_buffer;}
  inline VK_imgui* get_vk_imgui(){return vk_imgui;}

  inline std::list<Struct_data*> get_list_data_scene(){return struct_vulkan->list_data_scene;}
  inline std::list<Struct_data*> get_list_data_glyph(){return struct_vulkan->list_data_glyph;}

private:
  Engine* engine;
  Struct_param* struct_param;
  Struct_synchro* struct_synchro;
  Window* window;
  Timer timer;
  Struct_vulkan* struct_vulkan;

  VK_render* vk_render;
  VK_imgui* vk_imgui;
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
  VK_physical_device* vk_physical_device;
  VK_frame* vk_frame;
  VK_canvas* vk_canvas;
  VK_drawing* vk_drawing;

  std::list<Object*> list_scene;
  std::list<Object*> list_glyph;
};

#endif
