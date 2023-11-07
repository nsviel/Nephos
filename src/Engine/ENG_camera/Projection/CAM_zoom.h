#ifndef CAM_ZOOM_H
#define CAM_ZOOM_H

#include "../struct_camera.h"
#include <ELE_specific/common.h>

class ELE_window;


class CAM_zoom
{
public:
  CAM_zoom(ELE_window* ele_window);
  ~CAM_zoom();

public:
  void compute_zoom_optic(Struct_camera* camera, float value);
  void compute_zoom_position(Struct_camera* camera, float value);

private:
};

#endif
