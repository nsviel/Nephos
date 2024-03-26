#pragma once


namespace k4n::structure{

struct Calibration{
  //---------------------------

  string state = "Wait validation";
  int ransac_nb_iter = 1000;
  float ransac_thres_sphere = 0.005;
  float ransac_thres_pose = 0.1;
  float ransac_thres_radius = 0.02;
  float ransac_search_diameter_x = 1;

  //---------------------------
};

}
