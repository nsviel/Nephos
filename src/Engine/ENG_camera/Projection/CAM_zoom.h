#ifndef CAM_ZOOM_H
#define CAM_ZOOM_H

#include "../struct_camera.h"
#include <ELE_specific/common.h>

class Window;


class CAM_zoom
{
public:
  CAM_zoom(Window* window);
  ~CAM_zoom();

public:
  void compute_zoom_optic(Struct_camera* camera, float value);
  void compute_zoom_position(Struct_camera* camera, float value);

private:
};

#endif
