#ifndef VK_ENGINE_H
#define VK_ENGINE_H

#include <VK_struct/VK_typedef.h>
#include <VK_struct/Struct_vk_entity.h>
#include <VK_main/Struct_vulkan.h>
#include <UTL_specific/common.h>
#include <UTL_base/Struct_image.h>
#include <Vulkan_namespace.h>

class Struct_vulkan;
class VK_surface;
class VK_instance;
class VK_device;
class VK_swapchain;
class VK_descriptor;
class VK_texture;
class VK_data;
class VK_viewport;
class VK_reload;
class VK_frame;
class VK_canvas;
class VK_extension;
class VK_pool;
class VK_drawing;
class VK_synchronization;
class FPS_counter;


class VK_engine
{
public:
  //Constructor / Destructor
  VK_engine(Struct_vulkan* struct_vulkan);
  ~VK_engine();

public:
  //Init function
  void init();
  void init_engine_presentation();
  void init_engine_headless();

  //Main functions
  void loop();
  void clean();

  //Specific function
  void device_wait_idle();
  void reload_shader(string shader, string subshader);

  //Data function
  void insert_object_in_engine(data::Object* object);
  void remove_object_in_engine(data::Object* object);

  //Renderpass function
  void add_renderpass_description(Struct_vk_renderpass* renderpass);
  Struct_vk_renderpass* get_renderpass(int i);
  Struct_vk_renderpass* get_renderpass_presentation(int i);

  inline Struct_vk_entity* get_canvas(){return &struct_vulkan->data.canvas;}
  inline std::list<Struct_vk_entity*> get_list_data(){return struct_vulkan->data.list_object;}
  inline void set_window(GLFWwindow* window){struct_vulkan->window.glfw_window = window;}

private:
  Struct_vulkan* struct_vulkan;
  VK_extension* vk_extension;
  VK_surface* vk_surface;
  VK_instance* vk_instance;
  VK_device* vk_device;
  VK_swapchain* vk_swapchain;
  vk::VK_renderpass* vk_renderpass;
  VK_descriptor* vk_descriptor;
  VK_texture* vk_texture;
  VK_pool* vk_pool;
  VK_data* vk_data;
  VK_viewport* vk_viewport;
  VK_reload* vk_reload;
  VK_synchronization* vk_synchronization;
  VK_frame* vk_frame;
  VK_canvas* vk_canvas;
  VK_drawing* vk_drawing;
  FPS_counter* fps_counter;

  Timer timer;
};

#endif
