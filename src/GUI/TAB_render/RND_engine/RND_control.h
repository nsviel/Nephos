#ifndef CONTROL_ENGINE_H
#define CONTROL_ENGINE_H

#include <Specific/common.h>

class GUI;
class Engine;
class Window;
class Camera;
class Window;
class Scene;
class Transformation;
class Param;


class RND_control
{
public:
  //Constructor / Destructor
  RND_control(GUI* gui);
  ~RND_control();

public:
  //Main function
  void run_control(ImVec2 center);

  //Keyboard
  void control_keyboard_oneAction();
  void control_keyboard_camMove();
  void control_keyboard_translation();

  //Mouse
  void control_mouse(ImVec2 center);
  void control_mouse_wheel();

private:
  Engine* engine;
  Param* param;
  Window* window;
  Scene* sceneManager;
  Camera* cameraManager;
  Transformation* transformManager;
};

#endif
