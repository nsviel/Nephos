#ifndef UI_MAsssIN_H
#define UI_MAsssIN_H

#include <imgui/core/imgui.h>
#include <imgui/core/imgui_impl_glfw.h>
#include <imgui/core/imgui_internal.h>
#include <imgui/vulkan/imgui_impl_vulkan.h>

class GUI_vulkan;
class ELE_window;


class UI_main
{
public:
  //Constructor / Destructor
  UI_main(ELE_window* ele_window);
  ~UI_main();

public:
  //Main functions
  void init_gui();
  void clean_gui_vulkan();
  void run_gui_main();

private:
  ELE_window* ele_window;
  GUI_vulkan* gui_vulkan;

  ImGui_ImplVulkanH_Window* wd;
};

#endif
