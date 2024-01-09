#pragma once

#include <Engine/Base/Struct_entity.h>
#include <Engine/Capture/K4A/Structure/Namespace.h>
#include <Engine/Data/Namespace.h>
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
  void destroy();
  void draw_cloud();

  //Capture function
  void run_capture();
  void restart_capture();
  void run_playback(string path);
  void stop_threads();
  void reset_color_configuration();

  inline eng::kinect::structure::Cloud* get_cloud(){return &cloud;}

public:
  eng::scene::Scene* eng_scene;
  eng::scene::Glyph* sce_glyph;
  eng::ope::Transformation* ope_transform;
  K4A_capture* k4a_capture;
  K4A_playback* k4a_playback;

  eng::kinect::structure::Cloud cloud;
  eng::kinect::structure::Device device;
  eng::kinect::structure::Synchro synchro;
  eng::kinect::structure::Playback playback;
  eng::kinect::structure::Player player;
  eng::kinect::structure::Recorder recorder;

  eng::kinect::structure::Color color;
  eng::kinect::structure::Depth depth;
  eng::kinect::structure::Infrared ir;
};
