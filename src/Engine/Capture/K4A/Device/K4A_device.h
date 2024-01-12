#pragma once

#include <Engine/Base/Struct_entity.h>
#include <Engine/Capture/K4A/Structure/Namespace.h>
#include <Engine/Scene/Namespace.h>
#include <Utility/Specific/common.h>

class K4A_capture;
class K4A_playback;
class Engine;


class K4A_device : public eng::data::Entity
{
public:
  //Constructor / Destructor
  K4A_device(Engine* engine);
  ~K4A_device();

public:
  //Main function
  void init();
  void reset();
  void destroy();
  void draw_cloud();

  //Capture function
  void run_capture();
  void restart_capture();
  void run_playback(string path);
  void stop_threads();
  void reset_color_configuration();

  inline k4n::structure::Cloud* get_cloud(){return &cloud;}

public:
  eng::scene::Scene* eng_scene;
  eng::scene::Glyph* sce_glyph;
  eng::ope::Transformation* ope_transform;
  K4A_capture* k4a_capture;
  K4A_playback* k4a_playback;

  k4n::structure::Cloud cloud;
  k4n::structure::Device device;
  k4n::structure::Synchro synchro;
  k4n::structure::Playback playback;
  k4n::structure::Player player;
  k4n::structure::Recorder recorder;

  k4n::structure::Color color;
  k4n::structure::Depth depth;
  k4n::structure::Infrared ir;
};
