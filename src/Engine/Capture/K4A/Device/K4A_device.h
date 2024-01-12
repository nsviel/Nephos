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

  inline k4a::stucture::Cloud* get_cloud(){return &cloud;}

public:
  eng::scene::Scene* eng_scene;
  eng::scene::Glyph* sce_glyph;
  eng::ope::Transformation* ope_transform;
  K4A_capture* k4a_capture;
  K4A_playback* k4a_playback;

  k4a::stucture::Cloud cloud;
  k4a::stucture::Device device;
  k4a::stucture::Synchro synchro;
  k4a::stucture::Playback playback;
  k4a::stucture::Player player;
  k4a::stucture::Recorder recorder;

  k4a::stucture::Color color;
  k4a::stucture::Depth depth;
  k4a::stucture::Infrared ir;
};
