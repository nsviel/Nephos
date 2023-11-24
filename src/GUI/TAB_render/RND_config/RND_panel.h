#ifndef GUI_RENDER_PANEL_H
#define GUI_RENDER_PANEL_H


struct RND_panel{
  //---------------------------

  bool show_engine_camera   = false;
  bool show_object   = false;
  bool show_set      = false;
  bool show_shader   = true;
  bool show_kinect   = true;
  bool show_database = false;
  bool show_profiler = true;
  bool show_scene    = true;
  bool show_option   = false;
  bool show_capture  = true;

  //---------------------------
};

#endif
